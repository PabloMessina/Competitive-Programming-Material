// tags: geometry 2D, two pointers, ternary search
#pragma GCC optimize("Ofast")
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
    Point unit() {
        double d = norm();
        return {x/d,y/d};
    }
};
double min_dist(Point& a, Point& b, Point& c, Point& d) {
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
    return ((a + ab * t) - (c + cd * t)).norm();
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cout.precision(10);
    int n, m;
    vector<Point> A, B;
    cin >> n;
    A.resize(n);
    for (auto& p : A) cin >> p.x >> p.y;
    cin >> m;
    B.resize(m);
    for (auto& p : B) cin >> p.x >> p.y;
    int i = 0, j = 0;
    Point a = A[0];
    Point b = B[0];
    Point nxt_a, nxt_b;
    double ans = 1e9;
    while (i+1 < n and j+1 < m) {
        double da = (A[i+1] - a).norm();
        double db = (B[j+1] - b).norm();
        if (da < db) {
            nxt_a = A[i+1];
            nxt_b = b + (B[j+1] - B[j]).unit() * da;
            ++i;
        } else if (db < da) {
            nxt_a = a + (A[i+1] - A[i]).unit() * db;
            nxt_b = B[j+1];
            ++j;
        } else {
            nxt_a = A[++i];
            nxt_b = B[++j];
        }
        ans = min(ans, min_dist(a, nxt_a, b, nxt_b));
        a = nxt_a;
        b = nxt_b;
    }
    cout << ans << '\n';
    return 0;
}