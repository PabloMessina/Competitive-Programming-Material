#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int n, s, a[3000];
const ll MOD = 998244353LL;
// intuition:
//   we want to count all distinct tuples (L, seq, R)
//   where seq is a sequence [i1, i2, ..., ik] of indices such that
//      L <= i1 < i2 < ... < ik <= R
//      and a[i1] + a[i2] + ... + a[ik] == s
// dp(i, c, flag):
//   number of ways of forming valid tuples (L, seq, R)
//   assuming that
//      1) we are making decisions about indices i, i+1, i+2, ..., n-1
//      (all previous indices are already fixed)
//      2) we still have to decide the position of 'L' (if flag == 0)
//          or we already decided it (if flag == 1)
//      3) we still have to choose array elements such that they add up to 'c'
///         (if c > 0), or we have to choose the position of R (if c == 0)
ll memo[3000][3001][2];
ll dp(int i, int c, int flag) {
    // base case 1: out of range -> 0 ways
    if (i == n) return 0;
    // base case 2: already solved
    ll& ways = memo[i][c][flag];
    if (ways != -1) return ways;
    // general case
    if (flag == 0) { // mode 0: we have decide position of 'L'
        ways = (dp(i, c, 1) + dp(i+1, c, 0)) % MOD;
    } else { // mode 1: we have to decide sequence of array elements
            // such that they add up to 'c' and then the position of 'R'
        ways = dp(i+1, c, 1); // skip element i
        if (a[i] < c) ways = (ways + dp(i+1, c - a[i], 1)) % MOD;
        if (a[i] == c) ways = (ways + dp(i+1, 0, 1) + 1) % MOD;
        if (c == 0) ways = (ways + 1) % MOD;
    }
    return ways;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> n >> s;
    rep(i,0,n) cin >> a[i];
    memset(memo, -1, sizeof memo);
    cout << dp(0,s,0) << '\n';
    return 0;
}