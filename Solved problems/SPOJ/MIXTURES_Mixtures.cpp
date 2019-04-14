// tags: DP (matrix chain multiplication)
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
int N;
int colors[100];
ll memo_smoke[100][100];
int memo_color[100][100];
// dp(i,j) = the minimum smoke that could be generated
//    among all possible ways of combining colors i, i+1, ..., j
ll dp(int i, int j) {
    // base case 1: already solved
    ll& ans = memo_smoke[i][j];
    if (ans != -1) return ans;
    // base case 2: a single color
    if (i == j) { 
        memo_color[i][i] = colors[i];
        return ans = 0;
    }
    // general case: i < j
    int& color = memo_color[i][j];
    ans = LLONG_MAX;
    rep(k,i,j-1) { // for each possible split point between i and j
        ll tmp = dp(i,k) + dp(k+1,j) + memo_color[i][k] * memo_color[k+1][j];
        if (tmp < ans) {
            ans = tmp;
            color = (memo_color[i][k] + memo_color[k+1][j]) % 100;
        }
    }
    return ans;
}
int main() {
    while (cin >> N) {
        rep(i,0,N-1) cin >> colors[i];
        memset(memo_smoke, -1, sizeof memo_smoke);
        cout << dp(0,N-1) << '\n';
    }
    return 0;
}