// tags: dp, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int N;
ll B[1000][1000];

ll vert_sum_memo[1000][1000];
ll vert_sum(int i, int j) {
    ll& ans = vert_sum_memo[i][j];
    if (ans != -1) return ans;
    if (i == 0) return ans = B[i][j];
    return ans = B[i][j] + vert_sum(i-1, j);
}

ll memo[1000][1000];
ll dp(int i, int j) {
    ll& ans = memo[i][j];
    if (ans != -1) return ans;
    ll op1 = vert_sum(i, j) + (j+1 < N-i ? dp(i, j+1) : (i > 0 ? dp(i-1, j+1) : 0));
    ll op2 = i > 0 ? dp(i-1, j) : 0;
    return ans = max(op1, op2);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N and N) {
        int r = 0, c = 0;
        rep(i,0,N) {
            rep(j,0,i+1) {
                cin >> B[r][c];
                memo[r][c] = -1;
                vert_sum_memo[r][c] = -1;
                if (r > 0) --r, ++c;
                else r = r+c+1, c = 0;
            }
        }
        cout << dp(N-1, 0) << '\n';
    }    
    return 0;
}