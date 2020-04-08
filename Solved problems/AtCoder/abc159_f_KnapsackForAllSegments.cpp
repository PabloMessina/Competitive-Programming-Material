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
int n, s, a[3000];
const ll MOD = 998244353LL;
ll memo[3000][3001][2];
ll dp(int i, int c, int b) {
    if (i == n) return c == 0;
    ll& ans = memo[i][c][b];
    if (ans != -1) return ans;
    if (b == 0) {
        ans = (dp(i, c, 1) + dp(i+1, c, 0)) % MOD;
    } else {
        assert (b == 1);
        ans = dp(i+1, c, 1);
        if (a[i] <= c) ans = (ans + dp(i+1, c - a[i], 1)) % MOD;
        if (c == 0) ans = (ans + 1) % MOD;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> n >> s;
    rep(i,0,n) cin >> a[i];
    rep(i,0,n) rep(j,0,s+1) rep(k,0,2) memo[i][j][k] = -1;
    cout << dp(0,s,0) << '\n';
    return 0;
}