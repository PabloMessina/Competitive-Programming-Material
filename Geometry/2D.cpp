#include "../c++_template.cpp"
// -------------------------------
const double PI = acos(-1);
const double EPS = 1e-12;
typedef double T;
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
    P neg() { return { -x, -y }; }
    P rot_ccw() { return { -y, x }; }
    P rot_cw() { return { y, -x }; }
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
    int quad() const { return (x >= 0) ? (y >= 0 ? 0: 3) : (y >= 0 ? 1 : 2); } // 0, 1, 2, 3        
    double angle() { return atan2(y, x); } // [-PI, PI] 
    P unit() { return (*this)/norm(); }
    bool operator<(const P& p) const { // smaller quadrant or same quadrant and to the right
        int q = quad(), qp = p.quad();
        return q != qp ? q < qp : ((*this)^p) > 0;
    }
    bool same_angle(const P& p) { // two vectors pointing to the same direction
        return quad() == p.quad() and ((*this)^p) == 0;
    }
};

T turn(P &a, P &b, P &c) { return (b-a)^(c-a); }

int turn_sign(P& a, P& b, P& c) { T t = turn(a,b,c); return t < 0 ? -1 : t == 0 ? 0 : 1; /* (t < -EPS) ? -1 : (t > EPS) ? 1 : 0; */ }

bool on_line(P& a, P& b, P& p) { return turn(a,b,p) == 0; /* abs(turn(a,b,p)) < EPS; */}

bool in_disk(P &a, P &b, P &p) { return (a-p)*(b-p) <= 0; /* (a-p)*(b-p) <= EPS; */ }

bool on_segment(P &a, P &b, P &p) { return on_line(a,b,p) && in_disk(a,b,p); }

double closest_t(P& a, P& b, P& p) { return -((a-p)*(b-a) / ((b-a)*(b-a)*2.)); }

/* ======================================================= */
/* Check if a segment is below another segment (wrt a ray) */
/* ======================================================= */
// i.e: check if a segment is intersected by the ray first
// Assumptions:
// 1) for each segment:
//  p1 should be LEFT (or COLLINEAR) and p2 should be RIGHT (or COLLINEAR) wrt ray
// 2) segments do not intersect each other
// 3) segments are not collinear to the ray
// 4) the ray intersects all segments
struct Segment { P p1, p2;};
Segment segments[100000]; // array of line segments
bool is_si_below_sj(int i, int j) { // custom comparator based on cross product
    Segment& si = segments[i];
    Segment& sj = segments[j];
    return (si.p1.x >= sj.p1.x) ?
        turn(si.p1, sj.p2, sj.p1) > 0:
        turn(sj.p1, si.p1, si.p2) > 0;
}
// this can be used to keep a set of segments ordered by order of intersection
// by the ray, for example, active segments during a SWEEP LINE
set<int, decltype(is_si_below_sj)> active_segments(is_si_below_sj); // ordered set


// Rectangle Intersection
bool do_rects_intersect(P& dl1, P& ur1, P& dl2, P& ur2) {
    return max(dl1.x, dl2.x) <= min(ur1.x, ur2.x) && max(dl1.y, dl2.y) <= min(ur1.y, ur2.y);
}

// Line Segment Intersection
bool do_segments_intersect(P& p1, P& q1, P& p2, P& q2) {
    int t11 = turn_sign(p1, q1, p2), t12 = turn_sign(p1, q1, q2);
    int t21 = turn_sign(p2, q2, p1), t22 = turn_sign(p2, q2, q1);
    if (t11 != t12 and t21 != t22) return true;
    if (t11 == t12 and t11 == 0) return on_segment(p1,q1,p2) or on_segment(p2,q2,p1);
    return false;
}

// Line - Line Intersection
// return whether straight lines <-a-b-> and <-c-d-> intersect each other at a specific point
// if they do, we assign values to t1 and t2 such that
//    a + (b - a) * t1 == c + (d - c) * t2
bool intersect_lines(const P& a, const P& b, const P& c, const P& d, double& t1, double& t2) {
    P c_d = c-d;
    P b_a = b-a;
    double x = b_a^c_d;
    if (x == 0) return false; /* if (abs(x) < EPS) */ // parallel
    P c_a = c-a;
    t1 = c_a^c_d/x;
    t2 = b_a^c_a/x;
    return true;
}

// Circle Intersection
struct Circle {
    P c;
    double r;
    Circle(P c, double r) : c(c), r(r) {}
    Circle(double x, double y, double r) : c(P(x, y)), r(r) {}
};
bool fully_outside(double r1, double r2, double d_sqr) {
    double tmp = r1 + r2; return d_sqr > tmp * tmp;
}
bool fully_inside(double r1, double r2, double d_sqr) {
    if (r1 > r2) return false;
    double tmp = r2 - r1; return d_sqr < tmp * tmp;
}
bool do_circles_intersect(Circle& c1, Circle& c2) {
    double dx = c1.x - c2.x, dy = c1.y - c2.y;
    double d_sqr = dx * dx + dy * dy;
    if (fully_inside(c1.r, c2.r, d_sqr)) return false;
    if (fully_inside(c2.r, c1.r, d_sqr)) return false;
    if (fully_outside(c1.r, c2.r, d_sqr)) return false;
    return true;
}

// Based on https://cp-algorithms.com/geometry/circle-line-intersection.html
// Circle - Line Intersection
// Returns whether a circle and a line intersect each other.
// There are 3 possible cases:
// 1) The line is tangent to the circle (one intersection point)
// 2) The line intersects the circle at two points
// 3) The line does not intersect the circle
// If there are 2 intersection points, we assign values to ip1 and ip2.
// If there is 1 intersection point, we assign values to ip1.
// If there are no intersection points, we return false.
struct Line {
    P p1, p2;
    Line(P p1, P p2) : p1(p1), p2(p2) {}
    Line(double x1, double y1, double x2, double y2) : p1(P(x1, y1)), p2(P(x2, y2)) {}
};
bool intersect_circle_line(Circle& c, Line& l, int& n, P& ip1, P& ip2) {
    // Calculate coefficients a, b, c for the line equation a*x + b*y + c = 0,
    // given the circle center (c.c.x, c.c.y), radius c.r, and the line l (l.p1, l.p2).

    // Step 1: Calculate line points relative to the circle center
    P p1 = l.p1 - c.c;
    P p2 = l.p2 - c.c;

    // Step 2: Calculate line co    efficients
    double a = p2.y - p1.y;
    double b = p1.x - p2.x;
    double cc = -a * p1.x - b * p1.y;

    // Step 3: Calculate the projected point (x0, y0): closest point on the line to the center (now (0, 0))
    double x0 = -a * cc / (a * a + b * b);
    double y0 = -b * cc / (a * a + b * b);

    // Step 4: Check number of intersection points by comparing squared distance from center to line
    // with the squared radius
    double sq = a * a + b * b;
    if (cc * cc > c.r * c.r * sq + EPS) {
        // Case 1: No intersection
        n = 0;
        return false;
    } else if (std::abs(cc * cc - c.r * c.r * sq) < EPS) {
        // Case 2: Tangent (one intersection)
        ip1 = P(x0 + c.c.x, y0 + c.c.y); // transform back to original coordinates
        n = 1;
        return true;
    } else {
        // Case 3: Two intersection points
        double d = c.r * c.r - cc * cc / sq;
        double mult = sqrt(d / sq);

        ip1 = P(x0 + b * mult + c.c.x, y0 - a * mult + c.c.y);
        ip2 = P(x0 - b * mult + c.c.x, y0 + a * mult + c.c.y);
        n = 2;
        return true;
    }
}

// Point - Line / Line Segment distance
// reference: https://stackoverflow.com/questions/849211/shortest-distance-between-a-point-and-a-line-segment
// get distance between p and projection of p on line <- a - b ->
double point_line_dist(P& p, P& a, P& b) {
    P d = b-a;
    double t = (d*(p-a)) / d.norm2();
    return (a + d * t - p).norm();
}
// get distance between p and truncated projection of p on segment a -> b
double point_segment_dist(P& p, P& a, P& b) {
    if (a==b) return (p-a).norm(); // segment is a single point
    P d = b-a; // direction
    double t = (d*(p-a)) / d.norm2();
    if (t <= 0) return (p-a).norm(); // truncate left
    if (t >= 1) return (p-b).norm(); // truncate right
    return (a + d * t - p).norm();
}

// Straight Line Hashing (integer coords)
// -----------------------------------------
// task: given 2 points p1, p2 with integer coordinates, output a unique
// representation {a,b,c} such that a*x + b*y + c = 0 is the equation
// of the straight line defined by p1, p2. This representation must be
// unique for each straight line, no matter which p1 and p2 are sampled.
tuple<ll,ll,ll> hash_line(const P& p1, const P& p2) {
    ll a = p1.y - p2.y;
    ll b = p2.x - p1.x;
    ll c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
    ll sgn = (a < 0 or (a == 0 and b < 0)) ? -1 : 1;
    ll g = __gcd(abs(a), __gcd(abs(b), abs(c))) * sgn;
    return make_tuple(a/g, b/g, c/g);
}
// task: given 2 points p1 and p2 with integer coords, return a pair {a, b}
// which is unique for all straight lines having the same slope as
// the straight line that goes through p1 and p2
pair<ll,ll> hash_slope(const P& p1, const P& p2) {
    ll dx = p2.x - p1.x;
    ll dy = p2.y - p1.y;
    ll sgn = (dx < 0 or (dx == 0 and dy < 0)) ? -1 : 1;
    ll g = __gcd(abs(dx), abs(dy)) * sgn;
    return {dx/g, dy/g};
}

// Circumcenter of 3 points
// reference: https://codeforces.com/blog/entry/22194
P bary(const P& A, const P& B, const P& C, double a, double b, double c) {
    return (A*a + B*b + C*c) / (a + b + c);
}
P circumcenter(const P& A, const P& B, const P& C) {
    double a = (B - C).norm2(), b = (C - A).norm2(), c = (A - B).norm2();
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
}

// Area of 2D non self intersecting Polygon
// based on Green's Theorem:
// http://math.blogoverflow.com/2014/06/04/greens-theorem-and-area-of-polygons/
double polygon_area(vector<P>& p) { // ** points must be sorted ccw or cw
    int n = p.size(); double a = 0;
    rep(i,0,n) { int j = (i+1) % n; a += (p[i].x + p[j].x) * (p[j].y - p[i].y); }
    return a * 0.5; // abs(a * 0.5) if points are cw
}

// Point in Polygon
// -----------------------------
// 1) Convex Polygons
// 1.1) O(N) method
bool in_convex_poly(P& p, vector<P>& cp) {
    int n = cp.size();
    rep(i,0,n) if (turn(cp[i], cp[(i+1)%n], p) < 0) return false;
    return true;
}
// 1.2) O(log N) method
bool in_triangle(P& a, P& b, P& c, P& x) {
    return turn(a, b, x) >= 0 and turn(b, c, x) >= 0 and turn(c, a, x) >= 0;
}
bool in_convexhull(P& p, vector<P>& ch) {
    if (turn(ch[0], ch[1], p) < 0) return false;
    if (turn(ch[0], ch.back(), p) > 0) return false;
    int l = 2, r = ch.size() - 1;
    while (l < r) {
        int m = (l+r) >> 1;
        if (turn(ch[0], ch[m], p) <= 0) r = m;
        else l = m+1;
    }
    return in_triangle(ch[0], ch[l-1], ch[l], p);
}
// ----------------------------------------------
// 2) General methods: for complex / simple polygons
// EvenOdd Rule (ray casting - crossing number)
bool above(P &a, P &p) { return p.y >= a.y; }
bool crosses_ray(P &a, P &p, P &q) {
    return (above(a, q) - above(a, p)) * turn(a, p, q) > 0;
}
bool in_polygon_evenodd(vector<P> &p, P a, bool strict = true) {
    int c = 0, n = p.size();
    rep(i,0,n) {
        int j = (i+1)%n; if (on_segment(p[i], p[j], a)) return !strict;
        c += crosses_ray(a, p[i], p[j]);
    }
    return c & 1;
}
// Nonzero Rule (winding number)
bool in_polygon_nonzero(vector<P> &pol, P p, bool strict = true) {
    int wn = 0, n = pol.size();
    rep(i,0,n) {
        int j = (i+1)%n; if (on_segment(pol[i], pol[j], p)) return !strict;
        P &a = pol[i], &b = pol[j];
        if (a.y <= p.y) {
            if (p.y < b.y and ((b-a)^(p-a)) > 0) ++wn; // upward & left
        } else {
            if (p.y >= b.y and ((b-a)^(p-a)) < 0) --wn; // downward & right
        }
    }
    return wn != 0; // nonzero
}

// Find extreme point in Convex Hull
// -----------------------------------
// given two points a and b defining a vector a -> b, and given a convex hull with points
// sorted ccw, find the index in the convex hull of the extreme point.
//  ** the extreme point is the "leftmost" point in the convex hull with respect to the
//     vector a -> b (if there are 2 leftmost points, pick anyone)
int extreme_point_index(P &a, P &b, vector<P> &ch) {
    int n = ch.size();
    P v = b - a;
    v = P(-v.y, v.x); // to find the leftmost point
    if (v*ch[0] >= v*ch[1] && v*ch[0] >= v*ch[n-1]) return 0;
    int l = 0, r = n;
    while (true) {
        int m = (l+r)/2;
        if (v*ch[m] >= v*ch[m+1] && v*ch[m] >= v*ch[m-1]) return m;
        int d1 = v*(ch[l + 1] - ch[l]) > 0;
        int d2 = v*(ch[m + 1] - ch[m]) > 0;
        int a = v*ch[m] > v*ch[l];
        if (d1) { if (d2 && a) l = m; else r = m; }
        else { if (!d2 && a) r = m; else l = m; }
    }
}

// Line Segment and Convex Hull Intersection
pair<int,int> find_crossing_edge(P& a, P& b, vector<P>& ch, int start, int end) {
    int o_ref = turn(a, b, ch[start]);
    int n = ch.size();
    int l = start, r = start + ((end - start + n) % n);
    while (l < r) {
        int m = (l+r) >> 1;
        if (turn(a, b, ch[m % n]) != o_ref) r = m;
        else l = m+1;
    }
    return {(l-1+n) % n, l%n};
}
ll det(P& a, P& b) { return a.x * b.y - a.y * b.x; }
bool find_line_line_intersection(P& a1, P& b1, P& a2, P& b2,
        long double& t1, long double& t2) {
    P d1 = b1 - a1;
    P d2 = b2 - a2;
    P _d2 = d2 * -1;
    ll detA = det(d1, _d2);
    if (detA == 0) return false;
    P b = a2 - a1;
    t1 = (long double)det(b, _d2)/(long double)detA;
    t2 = (long double)det(d1, b)/(long double)detA;
    return true;
}
void find_segment_convexhull_intersection(P& a, P& b, vector<P>& ch) {
    // find rightmost and leftmost points in convex hull wrt vector a -> b
    int i1 = extreme_point_index(a, b, ch);
    int i2 = extreme_point_index(b, a, ch);
    // make sure the extremes are not to the same side
    int t1 = turn(a, b, ch[i1]);
    int t2 = turn(a, b, ch[i2]);
    if (t1 == t2) return; // all points are to the right (left) of a -> b (no intersection)
    // find 2 edges in the convex hull intersected by the straight line <- a - b ->
    pair<int,int> e1 = find_crossing_edge(a, b, ch, i1, i2); // binsearch from i1 to i2 ccw
    pair<int,int> e2 = find_crossing_edge(a, b, ch, i2, i1); // binsearch from i2 to i1 ccw
    // find exact intersection points
    long double r1, s1, r2, s2;
    assert(find_line_line_intersection(a, b, ch[e1.first], ch[e1.second], r1, s1));
    assert(find_line_line_intersection(a, b, ch[e2.first], ch[e2.second], r2, s2));
    // make sure intersections are significant and within line segment range
    if (r1 > 1.0 - EPS and r2 > 1.0 - EPS) return; // intersections above line segment
    if (r1 < EPS and r2 < EPS) return; // intersections below line segment
    if (abs(r1 - r2) < EPS) return; // insignificant intersection in a single point    
    if (r1 > r2) swap(r1, r2), swap(e1, e2), swap(s1, s2); // make sure r1 < r2
    // ** HERE DO WHATEVER YOU WANT WITH INTERSECTIONS FOUND
    //   1) a + (b-a) * max(r1, 0)  <--- first point of segment a -> b inside convex hull
    //      if r1 < 0, point a is strictly inside the convex hull
    //   2) a + (b-a) * min(r2, 1)  <--- last point of segment a -> b inside convex hull
    //      if r2 > 1, point b is strictly inside the convex hull
    cout << "(significant) intersection detected!\n";
}

// Check if at least one pair of segments intersect among many
// ----------------------------------------------------------
// given a list of segments, check if at least one pair of segments intersect
// in O(N log N) time complexity with a sweep line algorithm
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
// Custom comparator for sorting segments
long double current_x; // current x coordinate for the sweep line
long double get_y(P& p1, P& p2, long double x) { // get y coordinate of a point on the segment
    if (p1.x == p2.x) return min(p1.y, p2.y); // vertical segment
    return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}
struct is_below {
    vector<Segment>& segments;
    is_below(vector<Segment>& segments) : segments(segments) {}
    bool operator()(int i, int j) const {
        Segment& si = segments[i];
        Segment& sj = segments[j];
        long double y1 = get_y(si.p1, si.p2, current_x);
        long double y2 = get_y(sj.p1, sj.p2, current_x);
        if (abs(y1 - y2) > EPS) return y1 < y2;
        return i < j; // if same y, sort by id to avoid collisions
    }
};
bool do_segments_intersect(int i, int j, vector<Segment>& segments) {
    Segment& si = segments[i];
    Segment& sj = segments[j];
    return do_segments_intersect(si.p1, si.p2, sj.p1, sj.p2);
}
bool do_at_least_one_pair_of_segments_intersect(vector<Segment>& segments) {    
    // Create events for each segment
    int n = segments.size();
    vector<Event> events;
    rep(i,0,n) {
        Segment& s = segments[i];
        if (s.p1.x > s.p2.x) swap(s.p1, s.p2);
        events.eb(s.p1, START, i);
        events.eb(s.p2, END, i);
    }
    sort(events.begin(), events.end());
    // Run sweep line
    multiset<int, is_below> active_segments = multiset<int, is_below>(is_below(segments));
    vector<set<int, is_below>::iterator> active_segments_it(n);
    for (auto& e : events) {
        current_x = e.p.x;
        Segment& cur_s = segments[e.id];
        if (e.type == START) {
            auto it = active_segments.insert(e.id);
            active_segments_it[e.id] = it;
            if (it != active_segments.begin()) {
                auto prev = std::prev(it);
                if (do_segments_intersect(e.id, *prev, segments)) return true;
            }
            auto next = std::next(it);
            if (next != active_segments.end()) {
                if (do_segments_intersect(e.id, *next, segments)) return true;
            }
        } else {
            auto it = active_segments_it[e.id];
            assert(it != active_segments.end());
            if (it != active_segments.begin() && std::next(it) != active_segments.end()) {
                auto prev = std::prev(it);
                auto next = std::next(it);
                if (do_segments_intersect(*prev, *next, segments)) return true;
            }
            active_segments.erase(it);
        }
    }
    return false;
}