// tags: DP, strings
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int K, N, M;
string a, b;

int memo2[1000][1000];
int maxmatch(int i, int j) {
    if (i >= N or j >= M) return 0;    
    int& ans = memo2[i][j];
    if (ans != -1) return ans;
    if (a[i] == b[j]) return ans = 1 + maxmatch(i+1, j+1);
    return ans = 0;
}

int memo[1000][1000][2];
int dp(int i, int j, bool z) {
    if (i >= N or j >= M) return 0;
    int& ans = memo[i][j][z];
    if (ans != -1) return ans;
    ans = 0;
    if (z and a[i] == b[j]) ans = 1 + dp(i+1, j+1, 1);
    if (maxmatch(i, j) >= K) ans = max(ans, K + dp(i+K, j+K, 1));
    ans = max(ans, dp(i+1, j, 0));
    ans = max(ans, dp(i, j+1, 0));
    return ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> K and K) {
        cin >> a >> b;
        N = a.size(), M = b.size();
        rep(i,0,N) rep(j,0,M) {
            rep(z,0,2) memo[i][j][k] = -1;
            memo2[i][j] = -1;
        }
        cout << dp(0,0,0) << '\n';
    }
    return 0;
}