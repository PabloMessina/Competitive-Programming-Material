// tags: extended euclidean algorithm, math
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------

ll gcdext(ll a, ll b, ll& x, ll& y) {
    ll r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
    r2 = a, x2 = 1, y2 = 0;
    r1 = b, x1 = 0, y1 = 1;
    while (r1) {
        q = r2 / r1;
        r0 = r2 % r1;
        x0 = x2 - q * x1;
        y0 = y2 - q * y1;
        r2 = r1, x2 = x1, y2 = y1;
        r1 = r0, x1 = x0, y1 = y0;        
    }
    ll g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y;
    return g;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        ll r, s, q; cin >> r >> s >> q;
        ll x, y, g;
        g = gcdext(r, s, x, y);
        // r * x + s * y = g
        // r * x * (q/g) + s * y * (q/g) = q
        // r * (x * (q/g) + k * s/g) + s * (y * (q/g) - k * r/g) = q
        // a = x * (q/g) + k * s/g > 0
        //     x * q + k * s > 0
        //     k * s > -x * q
        //     k < -x * q / s
        // b = y * (q/g) - k * r/g > 0
        //     y * q - k * r > 0
        //     k * r < y * q
        //     k < y * q / r
        ll k = min(-x * q / (double)s, y * q / (double)r);
        ll a = x * (q/g) + k * (s/g);
        ll b = y * (q/g) - k * (r/g);
        if (a <= 0 or b <= 0) {
            a -= s/g;
            b += r/g;
        }
        cout << a << ' ' << b << '\n';
    }
    return 0;
}