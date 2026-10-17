// tags: combinatorics, binomial coefficients, modular arithmetics, fermat's little theorem
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
// answer = C(n, a) * C(m, b) * C(x, a+b) * (a+b)!
//   which apples, which melons, which pedestals, and how to arrange the
//   a+b distinct fruits on the chosen pedestals
const ll MOD = 1000000007ll; // a prime number
const int MAXN = 1000000;

ll binary_exp(ll a, ll b, ll m) {
    a %= m;
    ll res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

// factorials + inverse factorials using Fermat's little theorem
ll fac[MAXN+1], inv_fac[MAXN+1];
void init() {
    fac[0] = 1;
    rep(i,1,MAXN+1) fac[i] = fac[i-1] * i % MOD;
    inv_fac[MAXN] = binary_exp(fac[MAXN], MOD-2, MOD); // Fermat
    invrep(i,MAXN,1) inv_fac[i-1] = inv_fac[i] * i % MOD;
}
ll choose(int n, int k) {
    if (k < 0 or k > n) return 0;
    return fac[n] * inv_fac[k] % MOD * inv_fac[n-k] % MOD;
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    int x, n, m, a, b; cin >> x >> n >> m >> a >> b;
    ll ans = choose(n, a) * choose(m, b) % MOD * choose(x, a + b) % MOD * fac[a + b] % MOD;
    cout << ans << '\n';
    return 0;
}
