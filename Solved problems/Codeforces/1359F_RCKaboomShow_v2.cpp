// tags: binary search, geometry 2D, sweep line, segment intersection detection, custom comparator
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------

const int MAXN = 25000 + 5;
const long double EPS = 1e-12;
const long double INF = 1e18;

typedef long double T;
struct P { // 2D
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    bool operator==(const P& p) const { return x==p.x && y == p.y; }
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    P operator/(T d) const { return {x/d, y/d}; }
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product
    T operator*(const P& p) const { return x*p.x + y*p.y; } // dot product
    T norm2() { return x*x + y*y; }
    T norm() { return sqrt(norm2()); }
    P unit() { return (*this)/norm(); }
};

enum EventType { START, END };
struct Event {
    P p; // point of the event
    EventType type; // type of the event
    int id; // id of the segment
    Event(P p, EventType type, int id) : p(p), type(type), id(id) {}
    bool operator<(const Event& e) const {
        if (abs(p.x - e.p.x) > EPS) return p.x < e.p.x;
        return type < e.type;
    }
};

struct Segment {
    P p1, p2;
    Segment(P p1, P p2) : p1(p1), p2(p2) {}
    Segment() {}
};

int n;
P X[MAXN], XD[MAXN], V[MAXN], D[MAXN];
long double S[MAXN];
Segment segments[MAXN];

// Custom comparator for sorting segments
long double current_x; // current x coordinate for the sweep line
long double get_y(P& p1, P& p2, long double x) { // get y coordinate of a point on the segment
    if (p1.x == p2.x) return min(p1.y, p2.y); // vertical segment
    return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}
struct is_below {
    bool operator()(int i, int j) const {
        Segment& si = segments[i];
        Segment& sj = segments[j];
        long double y1 = get_y(si.p1, si.p2, current_x);
        long double y2 = get_y(sj.p1, sj.p2, current_x);
        if (abs(y1 - y2) > EPS) return y1 < y2;
        return i < j; // if same y, sort by id to avoid collisions
    }
};

T turn(P &a, P &b, P &c) { return (b-a)^(c-a); }
int turn_sign(P& a, P& b, P& c) { T t = turn(a,b,c); return (t < -EPS) ? -1 : (t > EPS) ? 1 : 0; }
bool on_line(P& a, P& b, P& p) { return abs(turn(a,b,p)) < EPS; }
bool in_disk(P &a, P &b, P &p) { return (a-p)*(b-p) <= EPS; }
bool on_segment(P &a, P &b, P &p) { return on_line(a,b,p) && in_disk(a,b,p); }

bool intersect_lines(const P& a, const P& b, const P& c, const P& d, double& t1, double& t2) {
    P c_d = c-d;
    P b_a = b-a;
    double x = b_a^c_d;
    if (abs(x) < EPS) return false; // parallel
    P c_a = c-a;
    t1 = c_a^c_d/x;
    t2 = b_a^c_a/x;
    return true;
}

bool do_segments_intersect(int i, int j, double t) {
    double ti, tj, t_collision;
    // Case 1: if lines intersect at a single point
    if (intersect_lines(X[i], XD[i], X[j], XD[j], ti, tj)) {
        if (ti < 0 or tj < 0) return false; // collision in the past
        P col_p = X[i] + D[i] * ti; // collision point
        double di = (col_p - X[i]).norm();
        ti = di / S[i]; // time to reach collision
        double dj = (col_p - X[j]).norm();
        tj = dj / S[j]; // time to reach collision
        t_collision = max(ti, tj);
    // Case 2: if lines are parallel
    } else {
        double s = 0;
        // if car i is moving towards car j
        if (on_line(X[i], XD[i], X[j]) and (XD[i] - X[i]) * (X[j] - X[i]) >= 0) s += S[i];
        // if car j is moving towards car i
        if (on_line(X[j], XD[j], X[i]) and (XD[j] - X[j]) * (X[i] - X[j]) >= 0) s += S[j];
        if (s == 0) return false; // cars are moving away from each other
        t_collision = (X[i] - X[j]).norm() / s;
    }
    return t_collision < t; // collision happens before time t
}

bool check_collision(long double t) {
    // Create events for each segment
    vector<Event> events;
    rep(i,0,n) {
        P p1 = X[i];
        P p2 = X[i] + V[i] * t;
        if (p1.x > p2.x) swap(p1, p2);
        segments[i] = Segment(p1, p2);
        events.eb(p1, START, i);
        events.eb(p2, END, i);
    }
    sort(events.begin(), events.end());
    // Run sweep line
    multiset<int, is_below> active_segments = multiset<int, is_below>(is_below());
    vector<set<int, is_below>::iterator> active_segments_it(n);
    for (auto& e : events) {
        current_x = e.p.x;
        Segment& cur_s = segments[e.id];
        if (e.type == START) {
            auto it = active_segments.insert(e.id);
            active_segments_it[e.id] = it;
            if (it != active_segments.begin()) {
                auto prev = std::prev(it);
                if (do_segments_intersect(e.id, *prev, t)) return true;
            }
            auto next = std::next(it);
            if (next != active_segments.end()) {
                if (do_segments_intersect(e.id, *next, t)) return true;
            }
        } else {
            auto it = active_segments_it[e.id];
            assert (it != active_segments.end());
            if (it != active_segments.begin() && std::next(it) != active_segments.end()) {
                auto prev = std::prev(it);
                auto next = std::next(it);
                if (do_segments_intersect(*prev, *next, t)) return true;
            }
            active_segments.erase(it);
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false); std::cin.tie(0);
    // Read input
    cin >> n;
    rep(i,0,n) {
        int x, y, dx, dy, s;
        cin >> x >> y >> dx >> dy >> s;
        X[i] = P(x, y);
        D[i] = P(dx, dy);
        S[i] = s;
        XD[i] = X[i] + D[i];
        V[i] = D[i].unit() * (long double)s; // velocity vector
    }
    // Binary search
    long double l = 0, r = INF;
    bool found = false;
    rep(_,0,100) {
        long double m = (l + r) / 2;
        if (check_collision(m)) {
            r = m;
            found = true;
        } else l = m;
    }
    if (found) {
        cout << fixed << setprecision(20) << (l + r) / 2 << "\n";
    } else {
        cout << "No show :(\n";
    }
    return 0;
}