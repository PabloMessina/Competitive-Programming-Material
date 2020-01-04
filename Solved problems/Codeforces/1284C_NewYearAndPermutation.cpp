// tags: math, modular arithmetics, combinatorics, counting
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
int n; ll m;
ll add(ll x, ll y) { return (x+y) % m; }
ll mul(ll x, ll y) { return (x*y) % m; }
vector<ll> memo;
ll fact(int k) {
    ll& ans = memo[k];
    if (ans != -1) return ans;
    if (k == 0) return ans = 1LL;
    return ans = mul(k, fact(k-1));
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> n >> m;
    ll ans = 0;
    memo.assign(n+1, -1);
    rep(k,1,n+1) {
        ans = add(ans, mul(mul(mul(fact(k), fact(n-k)), n-k+1), n-k+1) );
    }
    cout << ans << '\n';
    return 0;
}