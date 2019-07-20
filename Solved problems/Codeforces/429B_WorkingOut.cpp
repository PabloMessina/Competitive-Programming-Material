// tags: dp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)

const int MAXN = 1000;
int N,M;
int DP1_to[MAXN][MAXN];
int DP2_to[MAXN][MAXN];
int DP1_fr[MAXN][MAXN];
int DP2_fr[MAXN][MAXN];
int A[MAXN][MAXN];

int dp1_to(int i, int j) {
    if (i < 0 or j < 0) return 0;
    int& ans = DP1_to[i][j];
    if (ans != -1) return ans;
    ans = max(dp1_to(i-1,j), dp1_to(i,j-1)) + A[i][j];
    return ans;
}

int dp2_to(int i, int j) {
    if (i >= N or j < 0) return 0;
    int& ans = DP2_to[i][j];
    if (ans != -1) return ans;
    ans = max(dp2_to(i+1,j), dp2_to(i,j-1)) + A[i][j];
    return ans;
}

int dp1_fr(int i, int j) {
    if (i >= N or j >= M) return 0;
    int& ans = DP1_fr[i][j];
    if (ans != -1) return ans;
    ans = max(dp1_fr(i+1,j), dp1_fr(i,j+1)) + A[i][j];
    return ans;
}

int dp2_fr(int i, int j) {
    if (i < 0 or j >= M) return 0;
    int& ans = DP2_fr[i][j];
    if (ans != -1) return ans;
    ans = max(dp2_fr(i-1,j), dp2_fr(i,j+1)) + A[i][j];
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    rep(i,0,N-1) rep(j,0,M-1) cin >> A[i][j];
    memset(DP1_to, -1, sizeof DP1_to);
    memset(DP2_to, -1, sizeof DP2_to);
    memset(DP1_fr, -1, sizeof DP1_fr);
    memset(DP2_fr, -1, sizeof DP2_fr);
    int ans = 0;
    rep(i,0,N-1) rep(j,0,M-1) {
        if (i-1 >= 0 and i+1 < N and j-1 >=0 and j+1 < M) {                    
            int tmp = 0;
            tmp = max(tmp, dp1_to(i-1,j) + dp2_to(i,j-1) +
                           dp1_fr(i+1,j) + dp2_fr(i,j+1));
            tmp = max(tmp , dp1_to(i,j-1) + dp2_to(i+1,j) +
                            dp1_fr(i,j+1) + dp2_fr(i-1,j));
            ans = max(ans, tmp);
        }
    }
    cout << ans << '\n';
    return 0;
}