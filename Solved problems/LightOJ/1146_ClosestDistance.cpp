// tags: ternary search, geometry 2D
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
struct Point {
    double x, y;
    Point operator+(const Point& p) const { return {x+p.x, y+p.y}; }
    Point operator-(const Point& p) const { return {x-p.x, y-p.y}; }
    Point operator*(double d) const { return {x*d, y*d}; }
    double norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
};
int main() {
    cout.precision(10);
    int t; cin >> t;
    Point a, b, c, d;
    rep(i,1,t+1) {
        cin >> a.x >> a.y >> b.x >> b.y >> c.x >> c.y >> d.x >> d.y;
        double l = 0., r = 1.;
        Point ab = b - a;
        Point cd = d - c;
        rep(_,0,100) {
            double d = (r-l)/3.0;
            double m1 = l + d;
            double m2 = r - d;
            double f1 = ((a + ab * m1) - (c + cd * m1)).norm2();
            double f2 = ((a + ab * m2) - (c + cd * m2)).norm2();
            if (f1 < f2) r = m2;
            else l = m1;
        }
        double t = (l+r) * 0.5;
        double ans = ((a + ab * t) - (c + cd * t)).norm();
        cout << "Case " << i << ": " << ans << '\n';
    }
    return 0;
}