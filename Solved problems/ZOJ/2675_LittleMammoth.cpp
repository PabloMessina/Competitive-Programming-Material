// tags: green's theorem, calculus, line integral, geometry 2D, dot product,
// quadratic equation
#include <bits/stdc++.h> // import everything in one shot
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

const double PI = acos(-1);
const double EPS = 1e-8;
struct Point {
    double x, y;
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator*(double c) const { return {x * c, y * c}; }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double norm2() { return x * x + y * y; }
    double angle() {
        double angle = atan2(y, x);
        if (angle < 0) angle += 2 * PI;
        return angle;
    }
};
Point C; double r, r2; // circle
Point p11, p12, p21, p22; // rectangle

bool point_inside_circle(Point& p) {
    double dx = C.x - p.x, dy = C.y - p.y;
    return dx * dx + dy * dy <= r2;
}

bool rectangle_inside_circle() {
    return
        point_inside_circle(p11) and
        point_inside_circle(p12) and
        point_inside_circle(p21) and
        point_inside_circle(p22);
}

bool circle_inside_rectangle() {
    return
        p11.x <= C.x - r and C.x + r <= p22.x and
        p11.y <= C.y - r and C.y + r <= p22.y;
}

enum EventType { START, END };
struct AngleEvent {
    double angle; EventType type;
    bool operator<(const AngleEvent& o) const { return angle < o.angle; }
};
double segment_integral(Point& A, Point& B, vector<AngleEvent>& angle_events) {
    // 1) we find the 2 values of t such that || A + (B-A)* t  -  C || = r
    // which reduces to solve a quadratic equation a*t^2 + b*t + c = 0
    Point AB = B - A;
    Point CA = A - C;
    double a = AB.norm2();
    double b = 2 * CA.dot(AB);
    double c = CA.norm2() - r2;
    double tmp = b*b - 4*a*c;
    // no real roots, no intersection between ray A->B and circle (C,r)
    if (tmp <= EPS) return 0;
    tmp = sqrt(tmp);
    double t1 = (-b-tmp)/(2*a);
    double t2 = (-b+tmp)/(2*a);
    // make sure the segment A-B does intersect the interior of the circle    
    if (t1 >= 1-EPS or t2 <= EPS) return 0; 

    // 2) find the extreme points at which segment A-B enters and exits the circle.
    // in case the circunsference intersects the segment A-B at a point strictly inside, save
    // the angle w.r.t the circle's center and whether it is a start angle or an end angle.
    Point ps;
    if (t1 > -EPS) {
        ps = A + AB * t1;
        angle_events.push_back({(ps-C).angle(), END});
    } else {
        ps = A;
    }
    Point pe;
    if (t2 < 1+EPS) {
        pe = A + AB * t2;
        angle_events.push_back({(pe-C).angle(), START});
    } else {
        pe = B;
    }
    // 3) return the line integral of the vector field <0, x> over subsegment ps -> pe
    // (we are just applying green's theorem here to compute the segment's contribution to the area)
    return 0.5 * (ps.x + pe.x) * (pe.y - ps.y);
}

// Computes the line integral of the vector field <0,x> over the arc of the circle from angle 'a' to angle 'b'
// This can be done using a parameterization of the arc in polar coordinates:
// x(t) = C.x + r * cos(t)
// y(t) = C.x + r * sin(t)
// a <= t <= b
// The final integral can be seen here:
// https://www.wolframalpha.com/input/?i=integral((x+%2B+r*cos(t))+*+derivative(y+%2B+r*sin(t))+*+dt,+t%3Da..b)
double arc_integral(double a, double b) {
    return C.x * r * (sin(b) - sin(a)) + r2 * 0.5 * (0.5 * (sin(2*b) - sin(2*a)) + b - a);
}

int main() {
    double x1,y1,x2,y2;
    while (scanf("%lf%lf%lf",&C.x, &C.y,&r)==3) { // read input for each case
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        r2 = r * r;
        // rectangle's 4 corners
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        p11 = {x1, y1};
        p21 = {x2, y1};
        p22 = {x2, y2};
        p12 = {x1, y2};
        // ---- special cases
        if (rectangle_inside_circle()) {
            printf("%lf\n", (x2 - x1) * (y2 - y1)); // area of rectangle
            continue;
        }
        if (circle_inside_rectangle()) {
            printf("%lf\n", PI * r2); // area of circle
            continue;
        }
        // ---- general case
        // 1) compute line integrals over portions of rectangle's sides that
        // are within the circle, and collect angles at which the circle enters/exits
        // the rectangle
        vector<AngleEvent> events;
        double area = 0;
        area += segment_integral(p11, p21, events);
        area += segment_integral(p21, p22, events);
        area += segment_integral(p22, p12, events);
        area += segment_integral(p12, p11, events);
        // 2) compute line integrals over arcs of the circle that lie inside the rectangle
        int n = events.size();        
        if (n > 0) {
            sort(events.begin(), events.end()); // sort angle events
            if (events[0].type == END) { // ugly case: the first event is END
                area += arc_integral(0, events[0].angle);
                for (int i = 1; i < n-2; i+=2) {
                    area += arc_integral(events[i].angle, events[i+1].angle);
                }
                area += arc_integral(events[n-1].angle, 2*PI);
            } else {
                for (int i = 0; i < n-1; i+=2) {
                    area += arc_integral(events[i].angle, events[i+1].angle);
                }
            }
        }
        printf("%.20lf\n", area);
    }
    return 0;
}