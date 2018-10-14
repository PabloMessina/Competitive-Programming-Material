// tags: DP, combinatorics, math, modular binomial coefficient
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const ll MOD = (ll)1e9 + 7;
int f[10];
ll inline mul(ll x, ll y) { return (x * y) % MOD; }
ll inline add(ll x, ll y) { return (x + y) % MOD; }

ll choose_memo[102][102];
ll choose(int n, int k) {
    ll& ans = choose_memo[n][k];
    if (ans != -1) return ans;
    if (n == k) return ans = 1;
    if (k == 0) return ans = 1;
    if (n < k) return ans = 0;
    return ans = add(choose(n-1, k), choose(n-1, k-1));
}

ll memo[10][11][52][52];
ll dp(int i, int s, int p, int n) {
    if (i == 10) return s == 0;
    ll& ans = memo[i][s][p][n];
    if (ans != -1) return ans;
    if (f[i] == 0) return ans = dp(i+1, s, p, n);
    int mink = max(f[i] - n, 0);
    int maxk = min(f[i], p);
    ll tmp = 0;
    rep(k,mink,maxk) {
        int ss = (11 + ((s - i * (2 * k - f[i])) % 11)) % 11;
        tmp = add(tmp, mul(mul(choose(p, k), choose(n, f[i] - k)),
            dp(i+1, ss, p - k, n - f[i] + k)));
    }
    return ans = tmp;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string line;
    memset(choose_memo, -1, sizeof choose_memo);
    while (cin >> line) {
        memset(f, 0, sizeof f);
        for (char c : line) f[c-'0']++;
        ll ans = 0;
        int len = line.size();
        int p = len / 2 + (len % 2);
        int n = len / 2;
        memset(memo, -1, sizeof memo);
        ans = dp(0, 0, p, n);
        if (f[0] > 0) {
            memset(memo, -1, sizeof memo);
            f[0]--;
            ans = add(ans, MOD - dp(0, 0, p-1, n));
        }
        cout << ans << endl;
    }
    return 0;
}