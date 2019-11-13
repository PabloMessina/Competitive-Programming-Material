// tags: geometry, randomized algorithms, dot product, cross product,
// smallest enclosing circle
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const double eps = 1e-8;
int N, M;
struct Point {
    double x, y, z;
    friend istream& operator >> (istream& in, Point& p) { return in >> p.x >> p.y >> p.z; }
    Point operator-(const Point& p) const { return {x - p.x, y - p.y, z - p.z }; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y, z + p.z }; }
    Point operator*(double s) const { return {x * s, y * s, z * s}; }
    Point operator/(double s) const { return {x / s, y / s, z / s}; }
    double norm2() { return x*x + y*y + z*z; }
    double norm() { return sqrt(norm2()); }
    Point unit() {
        double d = norm();
        return { x / d, y / d, z / d };
    }
    Point cross(const Point& p) {
        return {
            y*p.z - z*p.y,
            z*p.x - x*p.z,
            x*p.y - y*p.x
        };
    }
    double dot(const Point& p) { return x * p.x + y * p.y + z * p.z; }
};

Point project(Point& p, Point& n) { return p - n * n.dot(p); }

Point bary(const Point& A, const Point& B, const Point& C, double a, double b, double c) {
    return (A*a + B*b + C*c) / (a + b + c);
}
Point circumcenter(const Point& A, const Point& B, const Point& C) {
    double a = (B - C).norm2(), b = (C - A).norm2(), c = (A - B).norm2();
    return bary(A, B, C, a*(b+c-a), b*(c+a-b), c*(a+b-c));
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    cout << setprecision(10) << fixed;
    vector<Point> spheres(N), proj(N);
    rep(i,0,N) cin >> spheres[i];
    while (M--) {
        double a, b, c; cin >> a >> b >> c;
        Point normal = {a, b, c};
        normal = normal.unit();
        rep(i,0,N) proj[i] = project(spheres[i], normal);
        random_shuffle(proj.begin(), proj.end());
        double r = 0;
        Point center = proj[0];
        rep(i,1,N) {
            if ((proj[i] - center).norm() > r + eps) {
                center = proj[i];
                r = 0;
                rep(j,0,i) {
                    if ((proj[j] - center).norm() > r + eps) {
                        center = (proj[i] + proj[j]) * 0.5;
                        r = (proj[i] - center).norm();
                        rep(k,0,j) {
                            if ((proj[k] - center).norm() > r + eps) {
                                center = circumcenter(proj[i], proj[j], proj[k]);
                                r = (proj[k] - center).norm();
                            }
                        }
                    }
                }
            }
        }
        cout << r << '\n';
    }
    return 0;
}