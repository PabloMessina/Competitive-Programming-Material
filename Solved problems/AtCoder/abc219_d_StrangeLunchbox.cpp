// tags: dynamic programming, knapsack, memoization
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
// DP(i, x, y) = minimum number of lunchboxes among i..N-1 that still get
// at least x more takoyaki and at least y more taiyaki.
// x and y are the remaining demand, so the original targets appear only in
// the first call, DP(0, X, Y). Each box is used at most once:
//   DP(i, x, y) = min( DP(i+1, x, y),  1 + DP(i+1, x-A[i], y-B[i]) )
// A negative remainder means that coordinate is already satisfied, so it is
// clamped to 0 before it is used as an index. INF is 1e9 rather than INT_MAX,
// because the take-transition adds 1 to the recursive answer.
const int INF = 1e9;
const int MAXN = 305;
int N, X, Y;
int A[MAXN], B[MAXN];
int memo[MAXN][MAXN][MAXN]; // -1 = not computed yet

int dp(int i, int x, int y) {
    if (x <= 0 && y <= 0) return 0; // both demands are already met
    if (i == N) return INF;         // boxes left, but no lunchboxes left
    x = max(x, 0);
    y = max(y, 0);
    int& ans = memo[i][x][y];
    if (ans != -1) return ans;
    ans = dp(i + 1, x, y);                                 // skip box i
    ans = min(ans, 1 + dp(i + 1, x - A[i], y - B[i]));     // buy box i
    return ans;
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> X >> Y;
    rep(i, 0, N) cin >> A[i] >> B[i];
    memset(memo, -1, sizeof(memo));
    int ans = dp(0, X, Y);
    cout << (ans >= INF ? -1 : ans) << '\n';
    return 0;
}
