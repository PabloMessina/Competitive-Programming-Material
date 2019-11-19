// tags: stacks, implementation, largest square in histogram
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
int N, M;
string board[1000];
int H[1000][1000], L[1000], R[1000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    rep(i,0,N) cin >> board[i];
    rep(i,0,N) {
        H[i][0] = 1;
        rep(j,1,M) {
            H[i][j] = 1;
            if (board[i][j] == board[i][j-1]) H[i][j] += H[i][j-1];
        }
    }
    vector<pair<int,int>> stack_;
    stack_.reserve(1000);
    int ans = 0;
    rep(j,0,M) {
        stack_.clear();
        stack_.emplace_back(0, 0);
        rep(i,0,N) {
            while (stack_.back().first >= H[i][j]) {
                stack_.pop_back();
            }
            L[i] = stack_.back().second;
            stack_.emplace_back(H[i][j], i+1);
        }
        stack_.clear();
        stack_.emplace_back(0, N);
        invrep(i,N-1,0) {
            while (stack_.back().first >= H[i][j]) {
                stack_.pop_back();
            }
            R[i] = stack_.back().second;
            stack_.emplace_back(H[i][j], i);
        }
        rep(i,0,N) {
            int d = min(R[i] - L[i], H[i][j]);
            ans = max(ans, d * d);
        }
    }
    cout << ans << '\n';
    return 0;
}