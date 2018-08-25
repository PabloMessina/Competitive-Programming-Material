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
    Point AB = B - A;
    Point CA = A - C;
    double a = AB.norm2();
    double b = 2 * CA.dot(AB);
    double c = CA.norm2() - r2;
    double tmp = b*b - 4*a*c;
    if (tmp <= EPS) return 0;
    tmp = sqrt(tmp);
    double t1 = (-b-tmp)/(2*a);
    double t2 = (-b+tmp)/(2*a);    
    if (t1 >= 1-EPS or t2 <= EPS) return 0;
    Point ps, pe;
    if (t1 > -EPS) {
        ps = A + AB * t1;
        angle_events.push_back({(ps-C).angle(), END});
    } else {
        ps = A;
    }
    if (t2 < 1+EPS) {
        pe = A + AB * t2;
        angle_events.push_back({(pe-C).angle(), START});
    } else {
        pe = B;
    }
    return 0.5 * (ps.x + pe.x) * (pe.y - ps.y);
}

double arc_integral(double a, double b) {
    double ans = C.x * r * (sin(b) - sin(a)) + r2 * 0.5 * (0.5 * (sin(2*b) - sin(2*a)) + b - a);
    return ans;
}

int main() {
    double x1,y1,x2,y2;
    while (scanf("%lf%lf%lf",&C.x, &C.y,&r)==3) {
        scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
        r2 = r * r;
        if (x1 > x2) swap(x1, x2);
        if (y1 > y2) swap(y1, y2);
        p11 = {x1, y1};
        p21 = {x2, y1};
        p22 = {x2, y2};
        p12 = {x1, y2};
        if (rectangle_inside_circle()) {
            printf("%lf\n", (x2 - x1) * (y2 - y1));
            continue;
        }
        if (circle_inside_rectangle()) {
            printf("%lf\n", PI * r2);
            continue;
        }
        vector<AngleEvent> events;
        double area = 0;
        area += segment_integral(p11, p21, events);
        area += segment_integral(p21, p22, events);
        area += segment_integral(p22, p12, events);
        area += segment_integral(p12, p11, events);
        int n = events.size();
        if (n > 0) {
            sort(events.begin(), events.end());
            if (events[0].type == END) {
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