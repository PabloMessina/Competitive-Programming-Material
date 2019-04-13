// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

int N;
ll memo[501][501];
// ways(n, h) = number of ways we can
//   build a starcaise with 'n' blocks
//   such that the first step uses 'h' vertical blocks
ll ways(int n, int h) {
    if (n < h) return 0; // base case 1: impossible
    if (n == h) return 1; // base case 2: only 1 way
    ll& ans = memo[n][h];
    if (ans != -1) return ans; // already solved
    // general case
    ll tmp = 0;
    rep(x,h+1,n-h) tmp += ways(n-h,x);
    return ans = tmp;
}

int main() {
    cin >> N;
    memset(memo, -1, sizeof memo);
    ll ans = 0;
    rep(h,1,N-1) ans += ways(N,h);
    cout << ans << '\n';
    return 0;
}