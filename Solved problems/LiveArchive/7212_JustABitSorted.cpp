// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b; i++)
typedef long long int ll;
#define MAXN 5000
const ll MOD = 1000000007;
int N,Q;
ll dp[MAXN+1][MAXN+1];
ll acc[MAXN+1];
inline ll sum(ll a, ll b) { return (a + b) % MOD; }
inline ll mult(ll a, ll b) { return (a * b) % MOD; }
int main() {
    while (scanf("%d%d", &N, &Q) == 2) {
        rep(n,1,N+1) {
            dp[n][1] = 1;
            rep(k,2,n+1) {
                dp[n][k] = mult(n-k+1, dp[n-1][k-1]);
                if (n-1 >= k) dp[n][k] = sum(dp[n][k], mult(k,dp[n-1][k]));
            }
        }
        acc[0] = 0;
        rep(k,1,N+1) acc[k] = sum(acc[k-1], dp[N][k]);
        rep(i,0,Q) {
            int q; scanf("%d", &q);
            if (i > 0) printf(" ");
            printf("%lld", acc[min(q, N)]);
        }
        puts("");
    }
    return 0;
}

// #pragma GCC optimize("Ofast")
// #include <bits/stdc++.h>
// using namespace std;
// // defines
// #define rep(i,a,b) for(int i = a; i < b; ++i)
// #define invrep(i,b,a) for(int i = b; i >= a; --i)
// #define umap unordered_map
// #define uset unordered_set
// #define ff first
// #define ss second
// // typedefs
// typedef pair<int,int> ii;
// typedef unsigned long long int ull;
// typedef long long int ll;
// // -------------------------------
// ll MOD = 1000000007;
// int N, Q;
// ll mul(ll a, ll b) { return (a * b) % MOD; }
// ll add(ll a, ll b) { return (a + b) % MOD; }
// ll memo[5001][5001];
// ll dp(int n, int k) {    
//     ll& ans = memo[n][k];
//     if (ans != -1) return ans;
//     if (k > n) return ans = 0;
//     if (n == 0) return ans = 0;
//     if (k == n) return ans = 1;
//     return ans = add(mul(n - k, dp(n-1, k-1)), mul(k, dp(n-1, k)));
// }
// ll memo_acc[5001][5001];
// ll dp_acc(int n, int k) {    
//     ll& ans = memo_acc[n][k];
//     if (ans != -1) return ans;
//     if (k == 0) return ans = 0;
//     return ans = add(dp_acc(n, k-1), dp(n, k));
// }
// int main() {
//     ios::sync_with_stdio(false); cin.tie(0);
//     memset(memo, -1, sizeof memo);
//     memset(memo_acc, -1, sizeof memo_acc);
//     while (cin >> N >> Q) {
//         rep(i,0,Q) {
//             int k; cin >> k;
//             if (i) cout << ' ';
//             cout << dp_acc(N, min(N, k));
//         }
//         cout << '\n';
//     }
//     return 0;
// }