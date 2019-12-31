// tags: math, modular inverse
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
const ll MOD = 998244353;

ll mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }
ll add(ll x, ll y) { return (x+y) % MOD; }
ll mul(ll x, ll y) { return (x*y) % MOD; }

ll gcdext(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    ll x1, y1;
    ll g = gcdext(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}
ll mulinv(ll a, ll m) {
    ll x, y;
    if (gcdext(a, m, x, y) == 1) return mod(x, m); // make sure 0 <= x < m
    return -1; // no inverse exists
}
ll mulinv(ll a) { return mulinv(a, MOD); }

int n;
vector<int> ks;
vector<vector<int>> wishes;
vector<ll> wish_count;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> n;
    ks.resize(n);
    wishes.resize(n);
    wish_count.assign(1000000, 0);
    rep(i,0,n) {
        cin >> ks[i];
        wishes[i].resize(ks[i]);
        rep(j,0,ks[i]) {
            cin >> wishes[i][j];
            wishes[i][j]--;
            wish_count[wishes[i][j]]++;
        }
    }
    ll k_prod = 1;
    for (int k : ks) k_prod = mul(k_prod, k);
    ll num = 0;
    rep(i,0,n) {
        ll s = 0;
        rep(j,0,ks[i]) s = add(s, wish_count[wishes[i][j]]);
        ll tmp = mul(mul(k_prod, mulinv(ks[i])),s);
        num = add(num, tmp);
    }
    ll den = mul(mul(k_prod, n),n);
    ll prob = mul(num, mulinv(den));
    cout << prob << '\n';
    return 0;
}