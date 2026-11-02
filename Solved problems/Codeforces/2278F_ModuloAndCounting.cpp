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
// Idea: write a_i mod a_{i+1} = a_i - k_i * a_{i+1}, with k_i = floor(a_i / a_{i+1}) >= 1.
// The modulo sum telescopes to (a_1 - a_n) - L, where L = sum (k_i - 1) * a_{i+1} >= 0
// is the "loss". Since a_1 <= m+2 and a_n >= 1, the loss budget is L <= 1. That forces:
//   - a_1 = m+2;
//   - every step is "slow" (k_i = 1, i.e. a_{i+1} <= a_i < 2*a_{i+1}), except possibly
//     a single step 2 -> 1 (the only step whose loss is exactly 1);
//   - after reaching 1, the array stays at 1.
// So a good array is a slow chain from m+2 down to 2, followed by zero or more 1s.
//
// DP: dp[i][v] = number of slow chains of length i that start at m+2 and end at v (v >= 2).
//   dp[1][m+2] = 1
//   dp[i][v] = sum_{x = v}^{min(2v-1, m+2)} dp[i-1][x]   (x can step slowly to v iff v <= x < 2v)
//   answer = sum_{i=2}^{n} dp[i][2]                     (pad with n-i ones)
// Prefix sums make each entry O(1), so O(n*m) per test with a single rolling row.
const ll MOD = 998244353;
signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        int S = m + 2;
        // dp[v] = number of zero-loss chains of the current length from S down to v
        vector<ll> dp(S + 1, 0), pref(S + 1, 0);
        dp[S] = 1;
        ll ans = 0;
        rep(i, 2, n + 1) {
            // prefix sums of the previous row must be built before dp is overwritten
            pref[1] = 0;
            rep(v, 2, S + 1) pref[v] = (pref[v-1] + dp[v]) % MOD;
            rep(v, 2, S + 1) {
                int r = min(2 * v - 1, S);
                dp[v] = (pref[r] - pref[v-1] + MOD) % MOD;
            }
            ans = (ans + dp[2]) % MOD;
        }
        cout << ans << '\n';
    }
    return 0;
}
