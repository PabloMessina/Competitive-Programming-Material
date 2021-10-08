// tags: DP + divide and conquer optimization
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef long long int ll;
#define MAXN 6000

int N;
ll B,C;
ll H[MAXN];
ll accH[MAXN];
ll accKH[MAXN];
ll dp[MAXN+1][MAXN];

ll deltaAccH(int i, int j) { return i > 0 ? accH[j] - accH[i-1] : accH[j]; }
ll deltaAccKH(int i, int j) { return i > 0 ? accKH[j] - accKH[i-1] : accKH[j]; }

// Compute total distance cost between i and j assuming that
// there is a station in both i and j
// (if i < 0, only in j)
// (if j >= N, only in i)
ll cost(int i, int j) {
    // station only in j
    if (i < 0) return j * accH[j] - accKH[j];

    // station only in i
    if (j >= N) return deltaAccKH(i, N-1) - i * deltaAccH(i, N-1);

    // normal case: both stations
    int ml = (i+j)/2;
    int mr = ml+1;
    ll left_cost = deltaAccKH(i, ml) - i * deltaAccH(i, ml);
    ll right_cost = j * deltaAccH(mr, j) - deltaAccKH(mr, j);
    return left_cost + right_cost;
}

// Solve DP[k][i] where i1 <= i <= i2 using divide and conquer optimization
// DP[k][i] = min { DP[k-1][j-1] + cost(j, i+1) for p1 <= j <= p2}
void fill(int k, int i1, int i2, int j1, int j2) {
    if (i1 > i2) return;
    int im = (i1+i2)/2;
    int jmin = max(j1, k-1);
    int jmax = min(j2, im);
    ll min_val = LLONG_MAX;
    int best_j = -1;
    rep(j,jmin,jmax) {
        ll val = cost(j,im+1) + (j > 0 ? dp[k-1][j-1] : 0);
        if (val < min_val) min_val = val, best_j = j;
    }
    dp[k][im] = min_val;
    fill(k,i1,im-1,j1,best_j);
    fill(k,im+1,i2,best_j,j2);
}

int main() {
    while (scanf("%d%lld%lld", &N, &B, &C) == 3) {
        rep(i,0,N) scanf("%lld", &H[i]);

        // -- precompute acc sums --
        accH[0] = H[0];
        accKH[0] = 0;
        rep(k, 1, N-1) {
            accH[k] = accH[k-1] + H[k];
            accKH[k] = accKH[k-1] + H[k] * k;
        }

        // -- DP --
        // k = 0
        rep(i,0,N-2) dp[0][i] = cost(-1, i+1);
        // k >= 1
        rep(k,1,N) fill(k,k-1,N-1,0,N-1);

        // -- print output --
        rep(k,1,N) {
            if (k > 1) printf(" ");
            ll total_cost = dp[k][N-1] * C + k * B;
            printf("%lld", total_cost);
        }
        puts("");
    }
    
    return 0;
}