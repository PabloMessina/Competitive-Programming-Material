// tags: geometry 2D, radial sweep line, cross product, segment intersection detection,
// straight line vector equation
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXK = 10000;
int S,K,W;
struct Point { ll x,y; };
struct Segment { Point a, b; };
Point kids[MAXK];
Segment walls[MAXK];

enum EventType { KID, WALL_START, WALL_END };
struct RadialEvent { // represents an event encountered in a radial sweep line
    EventType type; // either KID, WALL_START or WALL_END
    Point pt; // coordinates of the event
    double angle; // angle of the event (measured counter-clockwise from a reference point)
    int index; // used for accessing additional data and/or as an ID
    RadialEvent(EventType t, Point pt, double a, int i): type(t), pt(pt), angle(a), index(i) {}
    bool operator<(const RadialEvent& rhs) const { // sort by angle
        return angle < rhs.angle;
    }
};

// returns whether point c is to the left (1), collinear (0) or to the right (-1) with respect
// to the ray (a -> b) based on the sign of the cross product (b - a) x (c - a)
int orientation(Point& a, Point& b, Point& c) {
    double dx0 = b.x - a.x, dy0 = b.y - a.y;
    double dx1 = c.x - a.x, dy1 = c.y - a.y;
    double cross = dx0 * dy1 - dx1 * dy0;
    return cross > 0 ? 1 : cross == 0 ? 0 : -1;
}

// returns whether segments p1q1 and p2q2 intersect, inspired by:
// https://www.geeksforgeeks.org/check-if-two-given-line-segments-intersect/
bool do_segments_intersect(Point& p1, Point& q1, Point& p2, Point& q2) {
    int o11 = orientation(p1, q1, p2);
    int o12 = orientation(p1, q1, q2);
    int o21 = orientation(p2, q2, p1);
    int o22 = orientation(p2, q2, q1);
    return o11 != o12 and o21 != o22;
}

namespace Solver {
    // global variables
    Point center;    
    Point target; // target, dirx and diry are updated with every radial event
    ll dirx, diry;
    
    // returns the distance from center to walls[i] in the direction
    // of the ray (center -> target). This distance can be obtained by solving for 'd'
    // in the line intersection equation in vector form:
    // center + (target - center) * d = walls[i].a + (walls[i].b - walls[i].a) * s
    // which can be done using cramer's rule:
    // https://math.stackexchange.com/questions/406864/intersection-of-two-lines-in-vector-form
    double distance(int i) {
        Segment& w = walls[i];
        ll dx = w.b.x - w.a.x;
        ll dy = w.b.y - w.a.y;
        ll den = dirx * dy - diry * dx;
        ll num = (w.a.x - center.x) * dy - (w.a.y - center.y) * dx;
        return (double)num/(double)den; 
    }
    bool wall_cmp(int i, int j) { return distance(i) < distance(j); }
    set<int, bool(*)(int,int)> active_walls(wall_cmp); // to keep track of active walls during radial sweep
    // Notice that we use an ordered set with a custom comparator to sort walls according to their distance
    // from the center in the direction of the ray (center -> target)

    // when we start the radial sweep, we need to make sure active_walls is properly initialized
    // with all the walls intersected by the ray (center -> target)
    void init_active_walls() {        
        active_walls.clear();
        rep(i,0,W-1) {
            Segment& w = walls[i];
            int oa = orientation(center, target, w.a);
            int ob = orientation(center, target, w.b);
            if (oa != ob and distance(i) > 0) active_walls.insert(i);
        }
    }

    void update_target(Point& p) {
        target = p;
        dirx = p.x - center.x;
        diry = p.y - center.y;
    }

    int count_visible_kids(Point& _center, vector<RadialEvent>& events) {
        center = _center; // update center
        int n = events.size();
        // 1) find first KID event -> we will start the radial sweep from this kid
        int start_i = 0;
        for (auto& e : events) {
            if (e.type == KID) {
                update_target(e.pt);
                init_active_walls();
                break;
            }
            start_i++;
        }
        if (start_i == n) return 0; // no kid found -> trivially return 0
        // 2) execute radial sweep
        int count = 0;
        rep(i,start_i,start_i+n-1) {
            auto& e = events[i % n];
            update_target(e.pt); // point to the new target
            switch(e.type) {
            case KID: {
                    // no active walls -> trivially visible
                    if (active_walls.size() == 0) { count++; continue; }
                    // check if the closest wall is between center and target
                    Segment& wall = walls[*active_walls.begin()];
                    if (!do_segments_intersect(center, target, wall.a, wall.b)) count++;                
                }
                break;
            case WALL_START:
                active_walls.insert(e.index); // add to active_walls
                break;
            case WALL_END:
                active_walls.erase(e.index); // remove from active_walls
                break;
            }
        }
        return count;
    }
}

int main() {
    while (scanf("%d%d%d", &S, &K, &W) == 3) {
        // read kids' coordinates
        rep(i,0,K-1) scanf("%lld%lld", &kids[i].x, &kids[i].y);
        // read walls' coordinates
        rep(i,0,W-1) {
            Segment& w = walls[i];
            scanf("%lld%lld%lld%lld", &w.a.x, &w.a.y, &w.b.x, &w.b.y);
        }
        // for each seeker kid
        rep(i,0,S-1) {
            // --- collect radial events ---
            vector<RadialEvent> events;
            // 1) KID events
            rep(j,0,K-1) if (i != j) {                
                double a = atan2(kids[j].y - kids[i].y, kids[j].x - kids[i].x);
                events.emplace_back(KID, kids[j], a, j);
            }
            // 2) WALL_START and WALL_END events 
            rep(j,0,W-1) {
                Point p1 = walls[j].a;
                Point p2 = walls[j].b;
                // make sure p1 comes before p2 counter-clockwise
                if (orientation(kids[i], p1, p2) < 0) swap(p1, p2);
                double a1 = atan2(p1.y - kids[i].y, p1.x - kids[i].x);
                double a2 = atan2(p2.y - kids[i].y, p2.x - kids[i].x);
                events.emplace_back(WALL_START, p1, a1, j);
                events.emplace_back(WALL_END, p2, a2, j);
            }            
            sort(events.begin(), events.end()); // sort radial events by angle
            // print answer for i-th kid
            printf("%d\n", Solver::count_visible_kids(kids[i], events));
        }
    }
    return 0;
}