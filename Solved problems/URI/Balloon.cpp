// tags: geometry, sweep line, cross product, implicit graph, DP, implementation
// explanation: http://www.icpc-bolivia.edu.bo/Entrenamiento/ICPC/BR_solucoes_regional_2013.pdf
// official test cases: http://maratona.ime.usp.br/hist/2013/primeira-fase/
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define uset unordered_set
#define ff ff
#define ss ss
// -------------------------------
const int MAXN = 100000;
int N, Q;
struct P {
    ll x, y;
    ll operator^(const P& p) const { return x*p.y - y*p.x; }
};
ll cross(P& a, P& b, P& c) { return (b-a)^(c-a); }
struct Segment { 
    P p1, p2;
    bool horizontal() { return p1.y == p2.y; }
};
Segment segments[MAXN];
ll balloon_x[MAXN]; // x coordinate of balloons
int seg_parent[MAXN]; // to store segments' parents in the dependency graph (forest)
int bal_parent[MAXN]; // to store balloons' parents in the dependency graph (forest)

// Event of the sweep line
enum Type {SEG_START, BALLOON, SEG_END};
struct Event {
    ll x, y; int type, index;
    bool operator<(const Event& o) const { return x < o.x; }
};

// Segment comparator for the active_segments set (ordered set) used to keep track
// of all segments intersected by the vertical sweep line at the current position.
// Segments are sorted by the order in which they are intersected (bottom-up).
// We use an ordered set because it enables efficient dynamic insertion and deletion
// of elements (O(log(n))) while keeping segments sorted at all times.
// ** Notice that we don't need to explicitly calculate the distance of intersection to sort.
// Instead, we use cross products to check orientations.
bool is_si_below_sj(int i, int j) {
    Segment& si = segments[i];
    Segment& sj = segments[j];
    return (si.p1.x >= sj.p1.x) ?
        cross(si.p1, sj.p2, sj.p1) > 0:
        cross(sj.p1, si.p1, si.p2) > 0;
}
set<int, decltype(is_si_below_sj)> active_segments(is_si_below_sj);

// ----------------------------
// functions to propagate coordinates through the dependency graph (following parent pointers)
// by using memoization (top-down DP) to avoid redundant computations.
pair<ll,ll> coords[MAXN];
bool done[MAXN];
void set_coords(int i) {
    if (done[i]) return;
    int p = seg_parent[i];
    Segment& seg = segments[i];
    ll x = (seg.p1.y > seg.p2.y) ? seg.p1.x : seg.p2.x;
    if (p == -1) { // no parent -> goes up endlessly
        coords[i] = {x, -1};
    } else {
        Segment& pseg = segments[p];
        if (pseg.horizontal()) { // horizontal parent
            coords[i] = {x, pseg.p1.y};
        } else { // tilted parent
            set_coords(p);
            coords[i] = coords[p];
        }
    }
    done[i] = true;
}
void find_final_position(int ball_i, ll& x, ll& y) {
    int p = bal_parent[ball_i];
    if (p == -1) { // no parent -> goes up endlessly
        x = balloon_x[ball_i];
        y = -1;
    } else {
        Segment& seg = segments[p];
        if (seg.horizontal()) { // horizontal parent
            x = balloon_x[ball_i];
            y = seg.p1.y;
        } else { // tilted parent
            set_coords(p); // top-down DP
            x = coords[p].ff;
            y = coords[p].ss;
        }
    }
}

int main() {
    while(cin >> N >> Q) { // for each test case
        vector<Event> events;
        rep(i,0,N) { // read segments
            ll x1,y1,x2,y2; cin >> x1 >> y1 >> x2 >> y2;
            if (x1 > x2) { swap(x1,x2); swap(y1,y2); } // make sure x1 < x2
            segments[i] = {{x1,y1},{x2,y2}};
            events.push_back({x1, y1, SEG_START, i}); // seg_start event
            events.push_back({x2, y2, SEG_END, i}); // seg_end event
        }
        rep(i,0,Q) { // read balloons
            ll x; cin >> x;
            events.push_back({x, 0, BALLOON, i}); // balloon event
            balloon_x[i] = x;
        }
        sort(events.begin(), events.end()); // sort events
        active_segments.clear(); // reset active_segments
        for (auto& e : events) { // for each event
            if (e.type == SEG_START) {                
                auto ret = active_segments.insert(e.index); // add to active_segments
                Segment& s = segments[e.index];
                if (s.p1.y > s.p2.y) { // if balloons go up through this corner
                    // we set the parent of this segment
                    auto next_it = next(ret.ff); // ++ret.ff
                    if (next_it == active_segments.end()) {
                        seg_parent[e.index] = -1;              
                    } else {
                        seg_parent[e.index] = *next_it;
                    }
                }
            } else if (e.type == SEG_END) {
                auto it = active_segments.find(e.index);
                Segment& s = segments[e.index];
                if (s.p2.y > s.p1.y) { // if balloons go up through this corner
                    // we set the parent of this segment
                    auto next_it = next(it);
                    if (next_it == active_segments.end()) {
                        seg_parent[e.index] = -1;
                    } else {
                        seg_parent[e.index] = *next_it;
                    }
                }
                active_segments.erase(it); // remove from active_segments
            } else if (e.type == BALLOON) { // set parent of balloon
                if (active_segments.size() == 0) {
                    bal_parent[e.index] = -1;
                } else {
                    bal_parent[e.index] = *active_segments.begin();
                }
            }
        }
        // answer queries with top-down DP over dependency graph
        memset(done, 0, sizeof(bool) * N);
        rep(i,0,Q) {
            ll x, y; find_final_position(i,x,y);
            if (y == -1) cout << x << '\n';
            else cout << x << ' ' << y << '\n';
        }
    }
    return 0;
}