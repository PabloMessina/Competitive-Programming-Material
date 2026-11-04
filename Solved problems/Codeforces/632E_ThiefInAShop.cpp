// tags: DP, unbounded knapsack, min-count DP, shift by minimum, math
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
// Idea: let m = min price and write every price as m + surcharge (v = a_i - m >= 0).
// Any choice of exactly k products costs k*m + s, where s = sum of the chosen surcharges.
// The cheapest product has surcharge 0, so it can fill any unused slot: s is achievable
// with exactly k products iff it can be built with AT MOST k products of positive surcharge.
//
// DP: dp[s] = min number of products whose surcharges sum to s.
//   dp[0] = 0, dp[s] = k+1 ("infinity") otherwise
//   dp[j] = min over surcharges v <= j of dp[j - v] + 1
// Answer: every k*m + s with dp[s] <= k (unreachable s keep k+1 and fail the test).
//
// Speed-up: process surcharges in increasing order; for surcharge v only j <= k*v matters,
// since at most k products with surcharges <= v sum to at most k*v.
// Total work: k * sum of distinct surcharges <= ~5e8 simple operations.
signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    vi a(n);
    for (int& x : a) cin >> x;
    sort(a.begin(), a.end());
    a.erase(unique(a.begin(), a.end()), a.end());
    int m = a[0];
    int maxs = k * (a.back() - m);
    vi dp(maxs + 1, k + 1);
    dp[0] = 0;
    rep(i, 1, (int)a.size()) {
        int v = a[i] - m;
        rep(j, v, k * v + 1) dp[j] = min(dp[j], dp[j - v] + 1);
    }
    rep(s, 0, maxs + 1) if (dp[s] <= k) cout << k * m + s << ' ';
    cout << '\n';
    return 0;
}
