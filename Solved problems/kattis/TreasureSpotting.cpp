#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
// -------------------------------
int W, P;
template<typename T>
struct Point<T> { // 2D
    T x, y;
    bool operator==(const Point<T>& p) const { return x==p.x && y == p.y; }
    Point<T> operator+(const Point<T>& p) const { return {x+p.x, y+p.y}; }
    Point<T> operator-(const Point<T>& p) const { return {x-p.x, y-p.y}; }
    Point<T> operator*(T d) const { return {x*d, y*d}; }
    Point<T> negative() { return { -x, -y }; }
    Point<T> rotate_ccw() { return { -y, x }; }
    Point<T> rotate_cw() { return { y, -x }; }
    Point<double> cast() { return {(double)x, (double)y}; }
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
    T dot(const Point<T>& p) const { return x*p.x + y*p.y; }
    T cross(const Point<T>& p) const { return x*p.y - y*p.x; }
    int quadrant() const { // 0, 1, 2, 3
        if (x >= 0) return y >= 0 ? 0: 3;
        return y >= 0 ? 1 : 2;
    }
    double angle() {
        double angle = atan2(y, x); // [-PI, PI]
        if (angle < 0) angle += 2 * PI; // [0, 2*PI]
        return angle;
    }
    Point<double> unit() {
        double d = norm();
        return {x/d,y/d};
    }
    bool operator<(const Point& p) const { // smaller quadrant or same quadrant and to the right
        int q = quadrant();
        int qp = p.quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
    bool operator==(const Point& p) const { // two vectors pointing to the same direction
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
};

bool do_segments_intersect(Point& p1, Point& q1, Point& p2, Point& q2) {
    int o11 = orientation(p1, q1, p2);
    int o12 = orientation(p1, q1, q2);
    int o21 = orientation(p2, q2, p1);
    int o22 = orientation(p2, q2, q1);
    if (o11 != o12 and o21 != o22) // general case -> non-collinear intersection
        return true;
    if (o11 == o12 and o11 == 0) { // particular case -> segments are collinear
        Point dl1 = {min(p1.x, q1.x), min(p1.y, q1.y)};
        Point ur1 = {max(p1.x, q1.x), max(p1.y, q1.y)};
        Point dl2 = {min(p2.x, q2.x), min(p2.y, q2.y)};
        Point ur2 = {max(p2.x, q2.x), max(p2.y, q2.y)};
        return do_rectangles_intersect(dl1, ur1, dl2, ur2);
    }
    return false;
}

struct Segment {
    Point<ll> a, b;
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> W >> P;
    Point<ll> T; cin >> T.x >> T.y;
    vector<Segment> pirates;
    vector<Segment> walls;
    rep(i,0,W) {
        ll x1, y1, x2, y2;
        walls.push_back({{x1,y1}, {x2,y2}});
    }
    rep(i,0,P) {
        ll x1, y1, x2, y2;
        pirates.push_back({{x1,y1}, {x2,y2}});
    }
    rep(i,0,P) {
        auto& p = pirates[i];
        Point<ll> dir = p.b - p.a;
        Point<ll> t_rel = t - p.a;
        if (t_rel.norm2() > dir.norm2() or dir.rotate_cw().cross(t_rel) > 0) {
            cout << "not visible\n";
            goto next;
        }
        rep(j,0,P) {
            if (j == i) continue;
            auto& p2 = pirates[j];
            Point<ll> p2_rel = p2.a - p.a;
            if (p2_rel == dir and p2_rel.norm2() <= dir.norm2()) {
                cout << "not visible\n";
                goto next;
            }
        }
        for (auto& w : walls) {
            if (do_segments_intersect(p.a, T, w.a, w.b)) {
                cout << "not visible\n";
                goto next;
            }
        }
        cout << "visible\n";
        next:;
    }
    return 0;
}