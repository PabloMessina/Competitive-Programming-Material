// TODO: finish this
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

const double eps = 1e-8;

template<typename T> struct P { // 2D
    T x, y;
    P<T> operator+(const P<T>& p) const { return {x+p.x, y+p.y}; }
    P<T> operator-(const P<T>& p) const { return {x-p.x, y-p.y}; }
    P<T> operator*(T d) const { return {x*d, y*d}; }
    P<T> operator/(T d) const { return {x/d, y/d}; }
    T operator*(const P<T>& p) const { return x*p.x + y*p.y; }
    T operator^(const P<T>& p) const { return x*p.y - y*p.x; }
    P<double> cast() { return {(double)x, (double)y}; }
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
    P<double> unit() { return this->cast()/norm(); }
};

double polygon_area(vector<P<ll>>& pol) {
    int n = pol.size();
    double area = 0;
    rep(i,0,n) {
        int j = (i+1) % n;
        area += (pol[i].x + pol[j].x) * (pol[j].y - pol[i].y);
    }
    return area * 0.5;
}

ll cross(P<ll>& a, P<ll>& b, P<ll>& c) { return (b - a) ^ (c - a); }

double intersect(P<ll>& a, P<ll>& b, P<ll>& c, P<ll>& d) {
    return (c - a) ^ (c - d) / (double) ((b - a) ^ (c - d));
}

double area_contribution(P<ll>& a, P<ll>& b, vector<vector<P<ll>>>& polygons, int poly_i) {
    int n = polygons.size();
    vector<pair<double,int>> e;
    rep(i,0,n) {
        if (i == poly_i) continue;
        auto& poly = polygons[i];
        int m = poly.size();
        rep(j,0,m) {
            int k = (j+1)%m;
            auto& c = poly[j];
            auto& d = poly[k];
            ll o1 = cross(a, b, c), o2 = cross(a, b, d);
            ll o3 = cross(c, d, a), o4 = cross(c, d, b);
            if (o1 > 0 and o2 <= 0 and o3 <= 0 and o4 > 0) { // entering
                e.emplace_back(intersect(a, b, c, d), 1);
            } else if (o1 < 0 and o2 >= 0 and o3 > 0 and o4 <= 0) { // exiting
                e.emplace_back(intersect(a, b, c, d), -1);
            } else if (i < poly_i and !o1 and !o2 and (b - a) * (d - c) > 0) { // collinear
                double t1 = max((c - a).cast() * (b - a).unit(), 0.0);
                double t2 = min((d - a).cast() * (b - a).unit(), 1.0);
                if (t1 < t2) {
                    e.emplace_back(t1, 1);
                    e.emplace_back(t2, -1);
                }
            }
        }
    }
    sort(e.begin(), e.end());
    double f = 0, t = 0;
    int c = 0;
    for (auto& p : e) {
        if (!c) f += p.first - t;
        c += p.second;
        t = p.first;
    }
    f += 1.0 - t;
    assert (-eps <= f and f <= 1.0 + eps);
    return 0.5 * (a.x + b.x) * (b.y - a.y) * f;
}


int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    vector<vector<P<ll>>> polygons(n);
    double area_sum = 0;
    for (auto& poly : polygons) {
        int m; cin >> m;
        poly.resize(m);
        for (auto& p : poly) cin >> p.x >> p.y;
        double area = polygon_area(poly);
        if (area < 0) reverse(poly.begin(), poly.end());
        area_sum += abs(area);
    }
    double area_union = 0;
    rep(i,0,n) {
        auto& poly = polygons[i];
        int m = poly.size();
        rep(j,0,m) {
            area_union += area_contribution(poly[j], poly[(j+1)%m], polygons, i);
        }
    }
    cout << setprecision(10) << fixed << area_sum << ' ' << area_union << '\n';
    return 0;
}