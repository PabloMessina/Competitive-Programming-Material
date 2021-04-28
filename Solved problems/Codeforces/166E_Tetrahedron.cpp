// tags: DP bottom-up, math, counting
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
const ll MOD = 1000000007;
ll add(ll x, ll y) { return (x + y) % MOD; }
ll mul(ll x, ll y) { return (x * y) % MOD; }
ll dp(int n) {
    ll ways0 = 1, ways1 = 0;
    rep(k,1,n+1) {
        ll ways0_ = mul(ways1, 3);
        ll ways1_ = add(ways0, mul(ways1, 2));
        ways0 = ways0_;
        ways1 = ways1_;
    }
    return ways0;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    cout << dp(n) << '\n';
    return 0;
}