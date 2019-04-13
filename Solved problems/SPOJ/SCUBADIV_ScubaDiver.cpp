// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;

int tot_ox, tot_nit;
int n;
int ox[1000], nit[1000], w[1000];
int memo[22][80][1000];

// minw(to, tn, i) =
//   minimum total weight necessary
//   to reach oxigen >= to and nitrogen >= tn
//   only considering cylinders i, i+1, ..., n-1
// if it's not possible -> return INT_MAX
int minw(int to, int tn, int i) {
    // base cases    
    if (to == 0 and tn == 0) return 0;
    if (i == n) return INT_MAX;
    // check if already solved
    int& ans = memo[to][tn][i];
    if (ans != -1) return ans;
    // general case
    int tmp = INT_MAX;
    // option 1: use i-th cylinder
    int s = minw(max(to-ox[i],0),max(tn-nit[i],0),i+1);
    if (s != INT_MAX) tmp = min(tmp, w[i] + s);
    // option 2: don't use i-th cylinder
    tmp = min(tmp, minw(to,tn,i+1));
    // return answer
    return ans = tmp;
}

int main() {
    int tests; cin >> tests;
    while (tests--) {
        cin >> tot_ox >> tot_nit;
        cin >> n;
        rep(i,0,n-1) cin >> ox[i] >> nit[i] >> w[i];
        memset(memo, -1, sizeof memo);
        cout << minw(tot_ox, tot_nit, 0) << '\n';
    }
    return 0;
}