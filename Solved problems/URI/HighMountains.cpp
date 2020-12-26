// tags: area of union of regions, polygon area, cross product,
// union of intervals, segment intersection detection, geometry,
// straight line equation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 1000;
int N;
struct Point { ll x, y; };
struct Segment {
    Point p1, p2;
    double m, n;
    Segment() {}
    Segment(Point p1, Point p2) : p1(p1), p2(p2) {
        m = (p2.y - p1.y) / (double) (p2.x - p1.x); // slope
        n = p1.y - m * p1.x; // intercept
    }
};
struct Range { // defines a range [a .. b]
    double a, b; 
    bool operator<(const Range& rhs) const {
        return a < rhs.a; // to sort ranges by their mininum values
    }
};
Segment sides[MAXN * 2];

// calculates the cross product (b - a) x (c - a)
// and returns orientation:
// LEFT (1):      c is to the left of  ray (a -> b)
// RIGHT (-1):    c is to the right of ray (a -> b)
// COLLINEAR (0): c is collinear to    ray (a -> b)
// inspired by: https://www.geeksforgeeks.org/orientation-3-ordered-points/
int orientation(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    ll cross = dx0 * dy1 - dx1 * dy0;
    return cross > 0 ? 1 : cross == 0 ? 0 : -1;
}

// checks if segments s1 and s2 intersect using cross product
bool do_sides_intersect(Segment& s1, Segment& s2, bool& collinear) {
    int o11 = orientation(s1.p1, s1.p2, s2.p1);
    int o12 = orientation(s1.p1, s1.p2, s2.p2);
    collinear = (o11 == o12 and o11 == 0);
    if (collinear) return true; // collinear intersection

    int o21 = orientation(s2.p1, s2.p2, s1.p1);
    int o22 = orientation(s2.p1, s2.p2, s1.p2);
    if (o11 != o12 and o21 != o22) return true; // general intersection

    return false; // no intersection
}

// check whether s1 is below s2 (from the point of view of a vertical ray pointing upwards
// that intersects both segments). This assumes that the projections of s1 and s2
// on the x-axis intersect.
bool is_s1_below_s2(Segment& s1, Segment& s2) {
    return s1.p1.x > s2.p1.x ?
        orientation(s1.p1, s2.p2, s2.p1) > 0 :
        orientation(s2.p1, s1.p1, s1.p2) > 0;
}

// Given segments s1 and s2, determines the range [left, right] in the x-axis
// in which s2 is ABOVE (i.e. hiding) s1, and appends such range to hidden_ranges.
// In the special case that s2 FULLY hides s1, then returns true (no range is appended).
// Otherwise, returns false.
bool check_if_fully_hidden_or_append_range(
        Segment& s1, Segment& s2, vector<Range>& hidden_ranges) {
    // if intervals [s1.p1.x, s1.p2.x] and [s2.p1.x, s2.p2.x] does not intersect
    // then we are trivially done
    if (s1.p1.x >= s2.p2.x or s1.p2.x <= s2.p1.x) return false;

    bool collinear;
    double left, right;
    if (do_sides_intersect(s1, s2, collinear)) { // if s1 and s2 intersect
        if (collinear) { // if they are collinear
            // we consider s1 as fully-hidden only if it is the smallest segment
            // (this allows us to ignore small collinear sides and only consider
            // the largest collinear side)
            return s1.p2.x - s1.p1.x < s2.p2.x - s2.p1.x; 
        } else { // non-collinear, they intersect in a single point
            assert(s1.m != s2.m); // sanity check, should be true
            double x_int = (s1.n - s2.n) / (s2.m - s1.m); // x-coord of intersection
            // Depending on the slopes, s2 is above s1 either
            // from x_int to right or from x_int to the left
            if (s2.m > s1.m) {
                left = x_int, right = min(s1.p2.x, s2.p2.x);
            } else {
                left = max(s1.p1.x, s2.p1.x), right = x_int;
            }            
            if (left <= s1.p1.x and s1.p2.x <= right) return true; // s1 is fully hidden
            if (left < right) hidden_ranges.push_back({left, right});
        }
    // if s1 and s2 do not intersect, but s2 is above s1 nonetheless
    } else if (is_s1_below_s2(s1, s2)) {
        left = max(s1.p1.x, s2.p1.x);
        right = min(s2.p2.x, s2.p2.x);
        if (left <= s1.p1.x and s1.p2.x <= right) return true; // s1 is fully hidden
        if (left < right) hidden_ranges.push_back({left, right});
    }
    return false;
}

// computes the area under segment 'side', but SKIPPING those subsegments whose projections
// on the x-axis correspond to hidden ranges. In other words, we calculate the area under
// non-hidden portions of segment 'side' (the gaps between unions of hidden ranges).
double compute_contribution_to_area(Segment& side, vector<Range>& hidden_ranges) {
    sort(hidden_ranges.begin(), hidden_ranges.end());
    double last_x = side.p1.x;
    double area = 0;
    for(Range& r : hidden_ranges) {
        if (last_x < r.a) { // gap detected
            double y1 = side.m * last_x + side.n; // straight line equation
            double y2 = side.m * r.a + side.n; // straight line equation
            area += (r.a - last_x) * (y1 + y2); // area under sub-segment * 2
            last_x = r.b;
        } else if (last_x < r.b) {
            last_x = r.b;
        }
    }
    if (last_x < side.p2.x) { // possible last gap between last_x and side.p2.x
        double y1 = side.m * last_x + side.n;
        double y2 = side.p2.y;
        area += (side.p2.x - last_x) * (y1 + y2); // area under sub-segment * 2
    }
    return area;
}

int main() {
    while(cin >> N) {
        if (N == -1) break;
        // ---- read input -----
        int j = 0;
        while(N--) {
            ll i,d,h; cin >> i >> d >> h;
            // duplicate i,d,h so that the middle m = (i+d)/2 is integer too
            i*=2; d*=2; h*=2;
            ll m = (i+d)/2;
            // save 2 sides as segments
            sides[j++] = Segment({i, 0}, {m, h}); 
            sides[j++] = Segment({m, h}, {d, 0});
        }
        N = j;
        // ---- compute area -----
        double area = 0;
        rep(i,0,N) { // for each segment
            Segment& si = sides[i];
            vector<Range> hidden_ranges;
            bool fully_hidden = false;
            rep(j,0,N) { // for each other segment
                if (i == j) continue;
                Segment& sj = sides[j];
                fully_hidden = check_if_fully_hidden_or_append_range(si, sj, hidden_ranges);
                if (fully_hidden) break;
            }
            if (!fully_hidden) area += compute_contribution_to_area(si, hidden_ranges);
        }
        // we divide by 8 to undo the duplication of x and y (2 * 2 = 4)
        // and because we didn't divide by 2 when calculating area under segments
        cout << setprecision(2) << fixed << (area/8) << '\n';
    }
    return 0;
}