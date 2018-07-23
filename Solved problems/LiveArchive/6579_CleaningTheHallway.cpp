// tags: area of union of regions, green's theorem, line integral, polar coordinates,
// trigonometry, cosine theorem, union of intervals, circle intersection detection,
// geometry
// Explanation: http://users.dsic.upv.es/swerc/ProblemSet2013/solutions.pdf
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

struct Ring { int x, y, r_in, r_out; };
struct Interval {
    double a, b; // interval = [a, b]
    bool operator<(const Interval& rhs) const { // custom comparator
        return a < rhs.a; // we sort based on a
    }
};
const double _2PI = 8 * atan(1);
const int MAXN = 500;
int N;
Ring rings[MAXN];

// checks if circle of radius r1 is fully outside circle of radius r2
// given that the distance square between their centers is d_sqr
bool is_fully_outside(int r1, int r2, int d_sqr) {
    int tmp = r1 + r2;
    return d_sqr >= tmp * tmp;
}

// checks if circle of radius r1 is fully inside circle of radius r2
// given that the distance square between their centers is d_sqr
bool is_fully_inside(int r1, int r2, int d_sqr) {
    if (r1 > r2) return false;
    int tmp = r2 - r1;
    return d_sqr <= tmp * tmp;
}

bool do_circles_intersect(int r1, int r2, int d_sqr) {
    if (is_fully_inside(r1, r2, d_sqr)) return false;
    if (is_fully_inside(r2, r1, d_sqr)) return false;
    if (is_fully_outside(r1, r2, d_sqr)) return false;
    return true;
}

// returns an equivalent angle (in radians) within range [0, 2PI]
double correct_angle(double angle) {
    while (angle < 0) angle += _2PI;
    while (angle >= _2PI) angle -= _2PI;
    return angle;
}

// appends the interval [angle_begin, angle_end] to intervals, making sure some special
// cases are properly handled
void append_interval(double angle_begin, double angle_end, vector<Interval>& intervals) {
    // 1) make sure angles are in range [0, 2PI]
    angle_begin = correct_angle(angle_begin);
    angle_end = correct_angle(angle_end);
    // 2) append
    if (angle_begin < angle_end) { // normal case
        intervals.push_back({angle_begin, angle_end});
    } else { // special case -> angle_begin >= angle_end
        // To make things easy for us, we can split this into two intervals:
        intervals.push_back({angle_begin, _2PI}); // [angle_begin, 2PI]
        intervals.push_back({0, angle_end}); // [0, angle_end]
        // * inspired by: https://stackoverflow.com/questions/27509979/data-structure-for-storing-angle-intervals
    }
}

// Given a circle (x,y,r) and a ring, this function appends to 'intervals' all the angular intervals (in radians)
// from the point of view of (x,y) in which the circunsference (x,y,r) is within the ring's region (i.e inside the
// ring's outer circle and outside the ring's inner circle).
// In the special case that the circle (x,y,r) is fully (100%) hidden within the ring's region, we return true.
// Otherwise, we return false.
bool check_if_fully_hidden_or_append_intervals(
        int x, int y, int r, Ring& ring, vector<Interval>& intervals) {

    int dx = ring.x - x;
    int dy = ring.y - y;
    int d_sqr = dx * dx + dy * dy; // square distance between centers
    
    // Case 1) NO intersections between circle and ring. There are 3 possible subcases:
    // 1.1) circle (x,y,r) is completely outside ring's outer circle
    // => no intersections => no intervals to add
    if (is_fully_outside(r, ring.r_out, d_sqr)) {
        return false;        
    }
    // 1.2) circle (x,y,r) is completely inside ring's inner circle
    // => no intersections => no intervals to add
    if (is_fully_inside(r, ring.r_in, d_sqr)) {
        return false;
    }
    // 1.3) ring's outer circle is completely inside circle (x,y,r)
    // => the whole ring is inside circle (x,y,r)
    // => no intersections => no intervals to add
    if (is_fully_inside(ring.r_out, r, d_sqr)) {
        return false;
    }

    // Case 2) There is intersection between circle and ring. There are 4 possible subcases:    
    bool intersect_out = do_circles_intersect(r, ring.r_out, d_sqr);
    bool intersect_in = do_circles_intersect(r, ring.r_in, d_sqr);
    // 2.1) circle intersects both ring's outer circle and ring's inner circle
    if (intersect_in && intersect_out) {
        // we append 2 angular intervals (we use trigonometry here, essentially atan2 and cosine theorem)
        // note that the intervals are always defined counter-clockwise
        double theta = atan2(dy, dx);
        double d = sqrt(d_sqr);
        double alpha_in = acos((r * r + d_sqr - ring.r_in * ring.r_in) / (2. * r * d));
        double alpha_out = acos((r * r + d_sqr - ring.r_out * ring.r_out) / (2. * r * d));
        append_interval(theta - alpha_out, theta - alpha_in, intervals);
        append_interval(theta + alpha_in, theta + alpha_out, intervals);
    // 2.2) circle intersects only ring's inner circle
    } else if (intersect_in) {
        double theta = atan2(dy, dx);
        double d = sqrt(d_sqr);
        double alpha_in = acos((r * r + d_sqr - ring.r_in * ring.r_in) / (2. * r * d));
        append_interval(theta + alpha_in, theta - alpha_in, intervals);
    // 2.3) circle intersects only ring's outer circle
    } else if (intersect_out) {
        double theta = atan2(dy, dx);
        double d = sqrt(d_sqr);
        double alpha_out = acos((r * r + d_sqr - ring.r_out * ring.r_out) / (2. * r * d));
        append_interval(theta - alpha_out, theta + alpha_out, intervals);
    // 2.4) circle doesn't intersect any of ring's circles
    // => this means circle (x,y,r) is 100% inside the ring
    } else {
        return true;
    }
    return false;
}

// Performs a line integral of the vector field (0,x) over the circular arc with center (x,y), radius r
// and angular range [a, b] (in radians).
// This comes from applying Green's Theorem to calculate areas of closed 2D regions (with no holes):
//  Area(region) = line_integral(x * dy) over the boundary.
//  In this case, we are doing the integral over an arc of the circumsference (x,y,r) between angles [a,b],
//  so we use polar coordinates to parameterize x(t) and y(t) as functions of t, i.e:
//      x(t) = x + r * cost(t)
//      y(t) = y + r * sin(t)
// =>   x(t) * dy(t) * dt =  (x + r * cos(t)) * derivate(y + r * sin(t)) * dt
//                        =  (x + r * cos(t)) * r * cost(t) * dt
// ** Notice that y goes away in the derivative, that's why we ignore it.
// The final integral can be seen here:
// https://www.wolframalpha.com/input/?i=integral((x+%2B+r*cos(t))+*+derivative(y+%2B+r*sin(t))+*+dt,+t%3Da..b)
//
// To gain more intuition about Green's Theorem to calculate areas:
//    https://mathinsight.org/greens_theorem_find_area
//    Green's Theorem: https://www.youtube.com/watch?v=a_zdFvYXX_c
//    78 - Finding area with Green's theorem: https://www.youtube.com/watch?v=42vEvHpXYP8
//    Green's Theorem: area under an arch | MIT 18.02SC Multivariable Calculus, Fall 2010: https://www.youtube.com/watch?v=KXof0q88xbg
double integral(int x, int r, double a, double b) {
    return x * r * (sin(b) - sin(a)) + r * r * 0.5 * (0.5 * (sin(2*b) - sin(2*a)) + b - a);
}

// given a circle (x,y,r) and a list of angular intervals [(a0, b0), ... , (a(n-1), b(n-1))]
// calculates the area of this circle by computing the typical line integral over its circumsference
// traveled ccw (based on Green's Theorem) BUT SKIPPING the arcs defined by the angular intervals.
// In other words, we only integrate over the gaps left in between the interval unions.
// ** y is ignored because it goes away in the integral.
double get_full_integral(int x, int r, vector<Interval>& intervals) {
    sort(intervals.begin(), intervals.end());
    double end = 0;
    double ans = 0;
    for (auto& i : intervals) {
        if (end < i.a) { // gap detected
            ans += integral(x, r, end, i.a); // integrate over the gap
            end = i.b;
        } else {
            end = max(end, i.b);
        }
    }
    if (end < _2PI) { // possible last gap between 'end' and 2PI
        ans += integral(x, r, end, _2PI); // integrate over the gap
    }
    return ans;
}

int main() {
    int T; scanf("%d", &T);
    rep(_case, 1, T) { // for each test case

        // ----- read input
        scanf("%d", &N);
        map<tuple<int,int,int>,int> unique_in_circles;
        map<tuple<int,int,int>,int> unique_out_circles;
        rep(i,0,N-1) {
            int x,y,D,d; scanf("%d%d%d%d", &x,&y,&D,&d);
            int r_in = max(D-d,0); // notice the max(D-d,0)
            int r_out = D+d;
            unique_in_circles[make_tuple(x,y,r_in)] = i;
            unique_out_circles[make_tuple(x,y,r_out)] = i;
            rings[i] = {x,y,r_in,r_out};
        }

        // ----- calculate the area of union of all rings
        double area = 0;

        // 1) compute contribution to the area of outer circles
        for (auto& p : unique_out_circles) {
            int x,y,r; tie(x,y,r) = p.first;
            int id = p.second;
            vector<Interval> intervals;
            bool fully_hidden = false;
            // collect angular intervals in which current outer circle is hidden by other rings
            rep(i,0,N-1) {
                if (i == id) continue;
                fully_hidden = check_if_fully_hidden_or_append_intervals(
                    x,y,r, rings[i], intervals
                );
                if (fully_hidden) break;
            }
            if (!fully_hidden) { // add contribution to area only if not fully hidden
                area += get_full_integral(x,r,intervals);
            }
        }
        // 2) compute contribution to the area of inner circles
        for (auto& p : unique_in_circles) {
            int x,y,r; tie(x,y,r) = p.first;
            int id = p.second;
            vector<Interval> intervals;
            bool fully_hidden = false;
            // collect angular intervals in which current inner circle is hidden by other rings
            rep(i,0,N-1) {
                if (i == id) continue;
                fully_hidden = check_if_fully_hidden_or_append_intervals(
                    x,y,r, rings[i], intervals
                );
                if (fully_hidden) break;
            }
            if (!fully_hidden) { // add contribution to area only if not fully hidden
                // notice we substract instead because inner circles should be traveled clockwise,
                // but the integral is computed counter-clockwise,
                // so we compensate that by substracting
                area -= get_full_integral(x,r,intervals);
            }
        }
        // print answer
        printf("Case %d: %lf\n", _case, area);
    }
    return 0;
}