// tags: CRT, chinese remainder theorem, math, modular arithmetics
#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;

ll inline mod(ll x, ll m) { 
    ll tmp = x % m;
    if (tmp < 0) tmp += m;
    return tmp;
}
ll inline mult(ll x, ll y, ll m) { return (x * y) % m; }
ll inline add(ll x, ll y, ll m) { return (x + y) % m; }

void xgcd(ll a, ll b, ll& g, ll& x, ll& y) {
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
    g = r2, x = x2, y = y2;
    // for debugging
    // assert (g == a * x + b * y);
    // assert (g == __gcd(a,b));
}

pair<ll,ll> CRT(ll r1, ll m1, ll r2, ll m2) {
    ll g, x, y; xgcd(m1, m2, g, x, y);
    if ((r1 - r2) % g != 0) return {-1, -1};
    ll z = m2/g;
    ll lcm = m1 * z;
    ll sol = add(mod(r1, lcm), m1*mult(mod(x,z),mod((r2-r1)/g,z),z), lcm);
    // for debugging
    // assert (0 <= sol and sol < lcm);
    // assert (sol % m1 == r1 % m1);
    // assert (sol % m2 == r2 % m2);
    return {sol, lcm};
}

int main() {
    int T; cin >> T;
    while (T--) {
        ll r1, m1, r2, m2;
        cin >> r1 >> m1 >> r2 >> m2;
        pair<ll,ll> ans = CRT(r1,m1,r2,m2);
        if (ans.first == -1) cout << "no solution\n";
        else cout << ans.first << " " << ans.second << '\n';
    }
    return 0;
}