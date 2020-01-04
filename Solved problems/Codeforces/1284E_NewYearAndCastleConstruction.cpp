// tags: geometry 2D, radial sweep line, two pointers
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
// -------------------------------
const double PI = acos(-1);
const double EPS = 1e-8;
template<typename T> struct Point { // 2D
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
        return atan2(y, x);
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
    bool same_angle(const Point& p) { // two vectors pointing to the same direction
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    vector<Point<ll>> pts;
    pts.reserve(n);
    rep(i,0,n) {
        ll x, y; cin >> x >> y;
        pts.push_back({x, y});
    }
    ll count = 0; 
    rep(i,0,n) {
        vector<Point<ll>> vecs;
        rep(j,0,n) {
            if (i == j) continue;
            vecs.push_back(pts[j] - pts[i]);
        }
        sort(vecs.begin(), vecs.end());
        int m = vecs.size();
        int jj = 0;
        count += (n-1) * (n-2) * (n-3) * (n-4) / 24LL;
        rep(j,0,m) {
            while (jj < j or vecs[j].cross(vecs[(jj+1) % m]) > 0) ++jj;
            ll k = jj - j;
            if (k >= 3) {
                ll tmp = (k * (k-1) * (k-2)) / 6LL;
                count -= tmp;
            }
        }
    }
    cout << count << '\n';
    return 0;
}