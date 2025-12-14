#pragma GCC optimize("Ofast")
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
int N; // Number of straight lines
double D; // Radius around (0,0)

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

struct Circle {
    P c;
    double r;
    Circle(P c, double r) : c(c), r(r) {}
    Circle(double x, double y, double r) : c(P(x, y)), r(r) {}
};

struct Line {
    P p1, p2;
    Line(P p1, P p2) : p1(p1), p2(p2) {}
    Line(double x1, double y1, double x2, double y2) : p1(P(x1, y1)), p2(P(x2, y2)) {}
};

// Based on https://cp-algorithms.com/geometry/circle-line-intersection.html
bool intersect_circle_line(Circle& c, Line& l, int& n, P& ip1, P& ip2) {
    // Calculate coefficients a, b, c for the line equation a*x + b*y + c = 0,
    // given the circle center (c.c.x, c.c.y), radius c.r, and the line l (l.p1, l.p2).

    // Step 1: Calculate line points relative to the circle center
    P p1 = l.p1 - c.c;
    P p2 = l.p2 - c.c;

    // Step 2: Calculate line coefficients
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

void insert_single_angle_interval(set<pair<double, double>>& angle_intervals, double angle1, double angle2) {
    // cout << "Inserting single angle interval: " << angle1 << " " << angle2 << '\n';
    assert (angle1 < angle2);
    // Insert and obtain pointer to the interval just inserted
    auto it = angle_intervals.insert({angle1, angle2}).first;
    set<pair<double, double>>::iterator erase_start_it, erase_end_it; // We will use these to erase the intervals that are no longer needed
    double angle_min = angle1, angle_max = angle2;
    bool erase_start_found = false;
    if (angle_intervals.begin() != it) { // Check overlapping with the previous interval
        // cout << "Checking overlapping with the previous interval" << '\n';
        auto prev_it = prev(it);
        if (prev_it->second > angle1) {
            // Overlap found
            // cout << "Overlap found with the previous interval" << '\n';
            angle_min = min(angle_min, prev_it->first);
            angle_max = max(angle_max, prev_it->second);
            erase_start_it = prev_it;
            erase_end_it = next(it);
            erase_start_found = true;
        }
    }
    // Check overlapping with the next intervals
    while (next(it) != angle_intervals.end()) {
        // cout << "Checking overlapping with the next interval" << '\n';
        auto next_it = next(it);
        if (next_it->first < angle2) {
            // Overlap found
            // cout << "Overlap found with the next interval" << '\n';
            angle_min = min(angle_min, next_it->first);
            angle_max = max(angle_max, next_it->second);
            erase_end_it = next(next_it);
            if (!erase_start_found) {
                erase_start_it = it;
                erase_start_found = true;
            }
            it = next_it;
        } else {
            // cout << "No overlap found with the next interval" << '\n';
            break;
        }
    }
    if (erase_start_found) {
        angle_intervals.erase(erase_start_it, erase_end_it);
        angle_intervals.insert({angle_min, angle_max});
    }
}

void insert_angle_interval(set<pair<double, double>>& angle_intervals, double angle1, double angle2) {
    if (angle1 > angle2) swap(angle1, angle2);
    // cout << "Inserting angle interval: " << angle1 << " " << angle2 << '\n';
    double delta = angle2 - angle1;
    if (delta < PI) {
        insert_single_angle_interval(angle_intervals, angle1, angle2);
    } else {
        // Special case -> angle1 and angle2 are more than 180 degrees apart
        // => we split the interval into two intervals: [-PI, angle1] and [angle2, PI]
        insert_single_angle_interval(angle_intervals, -PI, angle1);
        insert_single_angle_interval(angle_intervals, angle2, PI);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> D;
    set<pair<double, double>> angle_intervals; // We will keep track of the angle intervals of the lines
    Circle c = {0, 0, D};
    int n;
    P ip1, ip2;
    rep(i,0,N) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        Line l = {P(x1, y1), P(x2, y2)};
        // Check if the line intersects the circle
        // cout << "----------------------- i = " << i << " -----------------------" << '\n';
        // cout << "Line: (" << x1 << ", " << y1 << ") (" << x2 << ", " << y2 << ")" << '\n';
        if (intersect_circle_line(c, l, n, ip1, ip2) and n == 2) {
            double angle1 = ip1.angle();
            double angle2 = ip2.angle();
            insert_angle_interval(angle_intervals, angle1, angle2);
            // cout << "Angle intervals:\n";
            // for (auto it = angle_intervals.begin(); it != angle_intervals.end(); ++it) {
            //     cout << "\t[" << it->first << ", " << it->second << "]" << '\n';
            // }
            if (angle_intervals.size() == 1) {
                auto it = angle_intervals.begin();
                double angle1 = it->first;
                double angle2 = it->second;
                if (angle1 - EPS < -PI and angle2 + EPS > PI) {
                    // The full circle is covered by the lines placed so far
                    cout << i + 1 << '\n'; // The bear got trapped at the (i+1)-th line
                    return 0;
                }
            }
        }  else {
            // cout << "No angle interval found" << '\n';
        }
    }
    cout << "*" << '\n'; // The bear always can reach the circumference of the circle
    return 0;
}