#include <bits/stdc++.h>
typedef long long int ll;
using namespace std;

ll inline mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }
ll inline mult(ll x, ll y, ll m) { return (x * y) % m; }
ll inline add(ll x, ll y, ll m) { return (x + y) % m; }

// extended euclidean algorithm
// finds g, x, y such that
//    a * x + b * y = g = GCD(a,b)
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

// CRT for a system of 2 modular linear equations
//   1) x = r1 (mod m1)
//   2) x = r2 (mod m2)
// sol = r1 + m1 * (r2-r1)/g * x' (mod LCM(m1,m2))
// where x' comes from
//   m1 * x' + m2 * y' = g = GCD(m1,m2)
//   where x' and y' are the values found by extended euclidean algorithm (xgcd)
pair<ll,ll> CRT(ll r1, ll m1, ll r2, ll m2) {
    ll g, x, y; xgcd(m1, m2, g, x, y);
    if ((r1 - r2) % g != 0) return {-1, -1}; // no solution
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
    while (1) {
        ll r1, m1, r2, m2;
        cin >> r1 >> m1 >> r2 >> m2;
        auto ans = CRT(r1,m1,r2,m2);
        if (ans.first == -1) cout << "no solution\n";
        else cout << ans.first << " " << ans.second << '\n';
    }
    return 0;
}