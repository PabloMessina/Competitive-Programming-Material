// tags: graphs, bfs/dfs, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int n, m;
string board[50];
bool reach[50][50];
int movr[4] = {0,1,-1,0};
int movc[4] = {1,0,0,-1};
void bfs() {    
    if (board[n-1][m-1] != '.') return;
    queue<pair<int,int>> q;
    reach[n-1][m-1] = true;
    q.emplace(n-1, m-1);
    while (!q.empty()) {
        int r, c; tie(r,c) = q.front(); q.pop();
        rep(i,0,4) {
            int rr = r + movr[i];
            int cc = c + movc[i];
            if (0 <= rr and rr < n and 0 <= cc and cc < m and board[rr][cc] != '#' and !reach[rr][cc]) {
                reach[rr][cc] = true;
                q.emplace(rr,cc);
            }
        }
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    nextcase:
    while (t--) {
        cin >> n >> m;
        rep(i,0,n) cin >> board[i];
        vector<pair<int,int>> good, bad;
        rep(i,0,n) rep(j,0,m) {
            if (board[i][j] == 'G') good.emplace_back(i,j);
            if (board[i][j] == 'B') bad.emplace_back(i,j);
        }
        if (good.empty() and bad.empty()) {
            cout << "Yes\n";
            continue;
        }
        for (auto& p : bad) {
            rep(i,0,4) {
                int rr = p.first + movr[i];
                int cc = p.second + movc[i];
                if (0 <= rr and rr < n and 0 <= cc and cc < m and board[rr][cc] == '.') {
                    board[rr][cc] = '#';
                }
            }
        }
        memset(reach, 0, sizeof reach);
        bfs();
        for (auto& p : good) {
            if (!reach[p.first][p.second]) {
                cout << "No\n";
                goto nextcase;
            }
        }
        for (auto& p : bad) {
            if (reach[p.first][p.second]) {
                cout << "No\n";
                goto nextcase;
            }
        }
        cout << "Yes\n";
    }
    return 0;
}