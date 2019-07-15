// tags: lagrange polynomial interpolation, modular arithmetics,
// modular inverse, gcdext
// references (and credits to):
// https://codeforces.com/blog/entry/23442
// https://en.wikipedia.org/wiki/Lagrange_polynomial
// https://en.wikipedia.org/wiki/Polynomial_interpolation#Uniqueness_of_the_interpolating_polynomial
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

const ll MOD = 1000000007;
int n, k;

ll mod(ll x) { return ((x %= MOD) < 0) ? x+MOD:x; }
ll mul(ll a, ll b) { return (a*b) % MOD; }
ll add(ll a, ll b) { return (a+b) % MOD; }

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

ll mulinv(ll a) {
    ll x, y;
    if (gcdext(a, MOD, x, y) == 1) return mod(x);
    return -1;
}

ll bin_exp(ll a, ll b, ll m) {	
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

ll calc(vector<ll>& ys, ll x) {
    ll res = 0;
    int sz = ys.size();
    ll num=1, den=1, k;
    rep(j,1,sz-1) {
        num = mul(num, mod(x - j));
        den = mul(den, mod(0 - j));
    }
    rep(i,1,sz-1) {
        num = mul(num, mul(mod(i-sz), mod(x-(i-1))));
        den = mul(den, mul(i, mod(x-i)));
        k = mul(num, mulinv(den));
        res = add(res, mul(ys[i], k));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> n >> k;
    vector<ll> ys(k+2);
    ys[0] = 0;
    rep(i,1,k+1) {
        ys[i] = (ys[i-1] + bin_exp(i,k,MOD)) % MOD;
    }
    ll ans = n <= k+1 ? ys[n] : calc(ys, n);
    cout << ans << '\n';
    return 0;
}