// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef long long int ll;
#define MAXN 5000
const ll MOD = 1000000007;
int N,Q;
ll dp[MAXN+1][MAXN+1];
ll acc[MAXN+1];
ll inline sum(ll a, ll b) { return (a + b) % MOD; }
ll inline mult(ll a, ll b) { return (a * b) % MOD; }
int main() {
    while (scanf("%d%d", &N, &Q) == 2) {
        rep(n,1,N) {
            dp[n][1] = 1;
            rep(k,2,n) {
                dp[n][k] = mult(n-k+1, dp[n-1][k-1]);
                if (n-1 >= k) dp[n][k] = sum(dp[n][k], mult(k,dp[n-1][k]));
            }
        }
        acc[0] = 0;
        rep(k,1,N) acc[k] = sum(acc[k-1], dp[N][k]);
        rep(i,1,Q) {
            int q; scanf("%d", &q);
            if (i > 1) printf(" ");
            printf("%lld", acc[min(q, N)]);
        }
        puts("");
    }
    return 0;
}