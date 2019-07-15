// tags: modular combinatorics, modular inverse, gcdext, math
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

const ll MOD = 1000000007;
int a,b,n;

ll inline mod(ll x) { return ((x %= MOD) < 0) ? x+MOD : x; }
ll inline mul(ll a, ll b) { return (a * b) % MOD; }
ll inline add(ll a, ll b) { return (a + b) % MOD; }

bool is_good(int x) {
    while (x > 0) {
        int d = x % 10;
        if (d != a and d != b) return false;
        x /= 10;
    }
    return true;
}

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

int main() {    
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> a >> b >> n;
    ll fact[n+1];
    fact[0] = 1;
    rep(i,1,n) fact[i] = mul(fact[i-1], i);
    ll ways = 0;
    rep(k,0,n) {
        if (is_good(a*k + (n-k)*b)) {
            ways = add(ways, mulinv(mul(fact[k], fact[n-k])));
        }
    }
    ways = mul(ways, fact[n]);
    cout << ways << '\n';
    return 0;
}