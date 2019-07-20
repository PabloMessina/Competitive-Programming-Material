// tags: sparse tables, DP, divide and conquer
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)

const int MAXN = 100000;
const int MAXLOG = 16;
int DP[MAXN][MAXLOG+1][2];
int S[MAXN];
int n, q;

int dp(int i, int e) {
    int& cand = DP[i][e][0];    
    if (cand != -1) return cand;
    int& dig = DP[i][e][1];
    if (e == 0) {
        dig = S[i];
        return cand = 0;
    }    
    int cand1 = dp(i,e-1);
    int cand2 = dp(i+(1<<(e-1)),e-1);
    int dig1 =  DP[i][e-1][1];
    int dig2 =  DP[i+(1<<(e-1))][e-1][1];
    dig = (dig1 + dig2) % 10;
    cand = cand1 + cand2 + (dig1 + dig2 >= 10);
    return cand;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    memset(DP, -1, sizeof DP);
    cin >> n;
    rep(i,0,n-1) cin >> S[i];
    cin >> q;
    while (q--) {
        int l,r; cin >> l >> r; l--, r--;
        int e = sizeof(int) * 8 - __builtin_clz(r-l+1) - 1;
        cout << dp(l,e) << '\n';
    }
    return 0;
}