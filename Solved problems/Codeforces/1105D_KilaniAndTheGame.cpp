// tags: bfs, graphs, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int movr[4] = {0, 1, -1, 0};
int movc[4] = {1, 0, 0, -1};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n, m, p; cin >> n >> m >> p;
    vector<string> board(n);
    vector<int> speed(p);
    rep(i,0,p) cin >> speed[i];
    rep(i,0,n) cin >> board[i];
    vector<queue<pair<int,int>>> qs(p), qs_aux(p);
    rep(i,0,n) rep(j,0,m) {
        char c = board[i][j];
        if (c != '.' and c != '#') {
            int k = c - '1';
            qs[k].emplace(i, j);
        }
    }
    while (true) {
        bool stop = true;
        rep(k,0,p) {
            int t = speed[k];
            while (t--) {
                while (!qs[k].empty()) {
                    int r,c; tie(r,c) = qs[k].front();
                    qs[k].pop();
                    rep(i,0,4) {
                        int rr = r + movr[i];
                        int cc = c + movc[i];
                        if (0 <= rr and rr < n and 0 <= cc and cc < m and board[rr][cc] == '.') {
                            board[rr][cc] = (char)('1' + k);
                            qs_aux[k].emplace(rr, cc);
                        }
                    }
                }
                swap(qs[k], qs_aux[k]);
                if (qs[k].empty()) break;
            }
            if (!qs[k].empty()) stop = false;
        }
        if (stop) break;
    }
    vector<int> counts(p,0);
    rep(r,0,n) rep(c,0,m) {
        if (board[r][c] == '#') continue;
        if (board[r][c] == '.') continue;
        counts[board[r][c] - '1']++;
    }
    rep(k,0,p) {
        if (k) cout << ' ';
        cout << counts[k];
    }
    cout << '\n';
    return 0;
}