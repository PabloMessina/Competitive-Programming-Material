// tags: geometry, two pointers, counting, combinatorics
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const double PI = acos(-1);
int N;
struct Point {
    int x, y;
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    double angle() { 
        double angle = atan2(y, x);
        if (angle < 0) angle += 2*PI;
        return angle;
    }
};
vector<Point> pts;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    pts.resize(N);
    rep(i,0,N-1) {
        cin >> pts[i].x >> pts[i].y;
    }
    vector<double> angles;
    angles.reserve(N-1);
    ll n_tri = ((ll)(N-1) * (N-2) * (N-3)) / 6ll;
    ll n_quad = ((ll)N * (N-1) * (N-2) * (N-3)) / 24ll;
    rep(i,0,N-1) {
        angles.clear();
        rep(j,0,N-1) {
            if (i == j) continue;
            angles.push_back((pts[j] - pts[i]).angle());
        }
        sort(angles.begin(), angles.end());
        int m = angles.size();
        int k = 0;
        ll count = 0;
        rep(j,0,m-1) {
            while (1) {
                double delta = angles[(k+1) % m] - angles[j];
                if (delta < 0) delta += 2*PI;
                if (delta >= PI or k+1-j+1 > m) break;
                ++k;
            }
            ll x = k-j;
            count += (x * (x-1)) / 2ll;
        }
        count = n_tri - count;
        n_quad -= count;
    }
    cout << n_quad << '\n';
    return 0;
}