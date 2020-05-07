// tags: DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;

const ll MOD = 1000000007;
int N, L;
int width[100], height[100];
ll memo[100][2][3001];
ll dp(int i, int o, int len) {
    ll& ans = memo[i][o][len];
    if (ans != -1) return ans;
    int w = width[i], h = height[i];
    if (o == 1) swap(w, h);
    if (w > len) return ans = 0;
    if (len == w) return ans = 1;
    ans = 0;
    rep(j,0,N) {
        if (i == j) continue;
        if (width[j] == h) ans = (ans + dp(j,0,len-w)) % MOD;
        if (width[j] != height[j] and height[j] == h) ans = (ans + dp(j,1,len-w)) % MOD;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> L;
    rep(i,0,N) cin >> width[i] >> height[i];
    memset(memo, -1, sizeof memo);
    ll ways = 0;
    rep(i,0,N) {
        ways = (ways + dp(i,0,L)) % MOD;
        if (width[i] != height[i]) {
            ways = (ways + dp(i,1,L)) % MOD;
        }
    }
    cout << ways << '\n';
    return 0;
}