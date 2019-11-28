// tags: DP
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N;
int D[10000], C[10000];
double memo[10001];
double discounts[6] = {1.0, 0.5, 0.25, 0.25, 0.25, 0.25};
double dp(int i) {
    double& ans = memo[i];
    if (ans > -0.5) return ans;
    if (i == N) return ans = 0;
    ans = 1e9;
    int max_j = min(i + 6, N);
    int acc_time = 0;
    double acc_cost = 0;
    rep(j,i,max_j) {
        if (acc_time >= 120) break;
        acc_cost += discounts[j-i] * C[j];
        ans = min(ans, acc_cost + dp(j+1));
        acc_time += D[j];
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N) cin >> D[i] >> C[i];
    rep(i,0,N+1) memo[i] = -1.0;
    cout << setprecision(2) << fixed;
    cout << dp(0) << '\n';
    return 0;
}