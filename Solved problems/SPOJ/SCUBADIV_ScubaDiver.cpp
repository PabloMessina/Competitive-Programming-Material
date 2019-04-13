// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

int tot_oxi, tot_nit, K;
int oxi[1000], nit[1000], w[1000];
int memo[22][80][1000];

// minw(o, n, i) =
//   minimum total weight necessary
//   o reach oxigen >= o and nitrogen >= n
//   only considering cylinders i, i+1, ..., n-1
// if it's not possible -> return INT_MAX
int minw(int o, int n, int i) {
    // base cases    
    if (o == 0 and n == 0) return 0;
    if (i == K) return INT_MAX;
    // check if already solved
    int& ans = memo[o][n][i];
    if (ans != -1) return ans;
    // general case
    ans = INT_MAX;
    // option 1: use i-th cylinder
    int s = minw(max(o-oxi[i],0),max(n-nit[i],0),i+1);
    if (s != INT_MAX) ans = min(ans, w[i] + s);
    // option 2: don't use i-th cylinder
    ans = min(ans, minw(o,n,i+1));
    // return answer
    return ans;
}

int main() {
    int tests; cin >> tests;
    while (tests--) {
        cin >> tot_oxi >> tot_nit;
        cin >> K;
        rep(i,0,K-1) cin >> oxi[i] >> nit[i] >> w[i];
        memset(memo, -1, sizeof memo);
        cout << minw(tot_oxi, tot_nit, 0) << '\n';
    }
    return 0;
}