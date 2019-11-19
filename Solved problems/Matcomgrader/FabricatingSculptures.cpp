// TODO: finish this, getting TLE
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD = 1000000007;
int S, B;
ll memo[5001][5001];
ll dp(int b, int s) {
    ll ans = memo[b][s];
    if (ans != -1) return ans;
    if (b == 0) return ans = 1;
    ans = 0;
    for (int k = 1; k <= min(b, s); ++k) {
        ans += ((s - k + 1) * dp(b - k, k)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> S >> B;
    rep(i,0,B+1) rep(j,0,S+1) memo[i][j] = -1;
    cout << dp(B - S, S) << '\n';
    return 0;
}