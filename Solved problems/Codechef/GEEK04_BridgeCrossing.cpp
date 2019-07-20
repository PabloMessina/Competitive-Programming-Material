// tags: dp, bitmask
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int T, N;
int A[20];
int DP[1 << 20];
int dp(int mask, int n) {
    int& ans = DP[mask];
    if (ans != -1) return ans;
    if (mask == 0) return ans = 0;
    if (n == 1) {
        rep(i,0,N-1) {
            if (mask & (1 << i)) {
                return ans = A[i];
            }
        }
    }
    ans = INT_MAX;
    int min_k = -1;
    int min_a = INT_MAX;
    if (n > 2) {
        rep(k,0,N-1) {
            if ((mask & (1 << k)) == 0) {
                if (min_a > A[k]) {
                    min_k = k;
                    min_a = A[k];
                }
            }
        }
    }
    rep(i,0,N-1) {
        int bi = 1 << i;
        if (mask & bi) {
            rep(j,0,N-1) {
                if (i == j) continue;
                int bj = 1 << j;
                if (mask & bj) {
                    int tmp = max(A[i],A[j]);
                    if (n > 2) {
                        int min_aa = min_a;
                        int min_kk = min_k;
                        if (min_aa > A[i]) {
                            min_aa = A[i];
                            min_kk = i;
                        }
                        if (min_aa > A[j]) {
                            min_aa = A[j];
                            min_kk = j;
                        }
                        int bkk = 1 << min_kk;
                        tmp += min_aa + dp(mask ^ bi ^ bj | bkk , n-1);
                    }
                    ans = min(ans, tmp);
                }
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> T;
    while (T--) {
        cin >> N;
        rep(i,0,N-1) cin >> A[i];
        memset(DP, -1, sizeof DP);
        cout << dp((1 << N)-1, N) << '\n';
    }
    return 0;
}