// tags: DP (LIS - longest increasing subsequence)
// source: https://www.quora.com/How-can-one-solve-the-Problem-MCARDS-on-SPOJ
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
int C, N, K;
int score[4];
struct Card {
    int color, value;
    bool operator<(const Card& rhs) const {
        if (color == rhs.color) return value < rhs.value;
        return score[color] < score[rhs.color];
    }
} cards[400];
int LIS() { // LIS = Longest Increasing Subsequence
// source: https://stackoverflow.com/questions/2631726/how-to-determine-the-longest-increasing-subsequence-using-dynamic-programming
    static int q[401];
    int len = 1;
    q[1] = 0;
    rep(i,1,K-1) {
        if (cards[q[len]] < cards[i]) {
            q[++len] = i;
        } else {
            int l=1, r=len;
            while (l < r) { // binary search
                int m = (l+r) >> 1;
                if (cards[i] < cards[q[m]]) r = m;
                else l = m+1;
            }
            q[l] = i;
        }
    }
    return len;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> C >> N;
    K = C*N;
    rep(i,0,K-1) { 
        cin >> cards[i].color >> cards[i].value;
        cards[i].color--;
    }
    rep(i,0,C-1) score[i] = i;
    int ans = INT_MAX;
    do { ans = min(ans, K - LIS()); }
    while (next_permutation(score, score+C)); // http://www.cplusplus.com/reference/algorithm/next_permutation/        
    cout << ans << '\n';
    return 0;
}