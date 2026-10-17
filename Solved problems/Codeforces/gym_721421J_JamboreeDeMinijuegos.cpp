// tags: game theory, DP, bottom-up, minimax, 2D prefix sums
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
// The board is always the square with top-left corner (x, x) and width w:
// taking the upper-left corner leaves (x+1, w-1), the lower-right leaves (x, w-1).
// DP(x, w) = best total for the player to move. After a move, the opponent
// gets DP(next) of the remaining square and we get the rest of it, so
//   DP(x, w) = sum(x, w) - min(DP(x+1, w-1), DP(x, w-1)),   DP(x, 0) = 0
const int MAXN = 2000;
ll pre[MAXN + 1][MAXN + 1]; // pre[i][j] = sum of a[0..i-1][0..j-1]

ll square_sum(int x, int w) {
    int y = x + w;
    return pre[y][y] - pre[x][y] - pre[y][x] + pre[x][x];
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    rep(i, 0, n) rep(j, 0, n) {
        ll a; cin >> a;
        pre[i + 1][j + 1] = a + pre[i][j + 1] + pre[i + 1][j] - pre[i][j];
    }
    // dp[x] = DP(x, w) for the current width w; starts as DP(x, 0) = 0
    vector<ll> dp(n + 1, 0);
    rep(w, 1, n + 1) {
        // increasing x: dp[x+1] still holds DP(x+1, w-1) when dp[x] is updated
        rep(x, 0, n - w + 1) {
            dp[x] = square_sum(x, w) - min(dp[x + 1], dp[x]);
        }
    }
    cout << dp[0] << '\n';
    return 0;
}