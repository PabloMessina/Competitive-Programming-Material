// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
int n, m;
int coins[50];
ll memo[251][50];
// ways(k, i) = number of ways we can
//   generate the amount of money 'k'
//   using coin types i, i+1, ..., m-1
ll ways(int k, int i) {
    if (k < 0) return 0; // base case: impossible
    if (k == 0) return 1; // base case: no money -> 1 way (use 0 coins)
    if (i == m) return 0; // base case: invalid coin type -> impossible
    ll& ans = memo[k][i];
    if (ans != -1) return ans; // base case: already solved
    // general case
    // option 1: don't use i-th coin type
    // option 2: use i-th coin type
    return ans = ways(k, i+1) + ways(k - coins[i], i);
    // ** se puede demostrar correctitud por inducción
}
int main() {
    cin >> n >> m;
    rep(i,0,m) cin >> coins[i];
    memset(memo, -1, sizeof memo);
    cout << ways(n,0) << '\n';
    return 0;
}