// tags: dp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD = 1000000007;
int S, B;
ll add(ll x, ll y) { return (x+y)%MOD; }
ll mul(ll x, ll y) { return (x*y)%MOD; }

ll dp(int s, int b);

ll memo_sum[5001][5001];
ll dp_sum(int s, int b) {
    ll& ans = memo_sum[s][b];
    if (ans != -1) return ans;
    if (s == 1) return ans = dp(s, b);
    return ans = add(dp(s, b), dp_sum(s-1, b));
}

ll memo_ss_sum[5001][5001];
ll dp_ss_sum(int s, int b) {
    ll& ans = memo_ss_sum[s][b];
    if (ans != -1) return ans;
    if (s == 1) return ans = dp(s, b);
    return ans = add(mul(dp(s, b),s), dp_ss_sum(s-1, b));
}

ll memo[5001][5001];
ll dp(int s, int b) {
    ll& ans = memo[s][b];
    if (ans != -1) return ans;
    if (s == b) return ans = 1;
    int bb = b - s;
    int k = min(s, bb);
    return ans = add(mul(1+s, dp_sum(k, bb)), MOD - dp_ss_sum(k, bb));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> S >> B;
    rep(s,0,S+1) rep(b,0,B+1) {
        memo[s][b] = -1;
        memo_sum[s][b] = -1;
        memo_ss_sum[s][b] = -1;
    }
    cout << dp(S, B) << '\n';
    return 0;
}