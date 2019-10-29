// tags: TSP, DP, BFS, bitwise, implicit graph
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int w, h;
string board[20];
int dist[11][20][20];
int movr[4] = {0,1,0,-1};
int movc[4] = {1,0,-1,0};
void bfs(int r, int c, int i) {
    queue<pair<int,int>> q;
    q.emplace(r, c);
    dist[i][r][c] = 0;
    while (!q.empty()) {
        tie(r,c) = q.front(); q.pop();
        rep(j,0,3) {
            int rr = r + movr[j];
            int cc = c + movc[j];
            if (0 <= rr and rr < h and 0 <= cc and cc < w and
                    board[rr][cc] != 'x' and dist[i][rr][cc] == -1) {
                dist[i][rr][cc] = dist[i][r][c] + 1;
                q.emplace(rr, cc);
            }
        }
    }
}

int cost[11][11];
int memo[1 << 11][11];
int dp(int mask, int i) {
    int& ans = memo[mask][i];
    if (ans != -1) return ans;
    int mask2 = mask & ~(1 << i);
    if (mask2 == 0) return ans = 0;
    ans = INT_MAX;
    for (int j = 0, tmp=mask2; tmp; ++j, tmp>>=1) {
        if (tmp & 1) ans = min(ans, cost[i][j] + dp(mask2, j));
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);    
    while (1) {
        cin >> w >> h;
        if (w == 0) break;
        rep(r, 0, h-1) cin >> board[r];
        int sr, sc;
        vector<pair<int,int>> dirty_coords;
        memset(dist, -1, sizeof dist);
        rep(r, 0, h-1) rep(c, 0, w-1) {
            char cell = board[r][c];
            if (cell == 'o') {
                sr = r, sc = c;
                bfs(r, c, 0);
            } else if (cell == '*') {
                dirty_coords.emplace_back(r, c);
                bfs(r, c, dirty_coords.size());
            }
        }
        bool possible = true;
        int i = 1;
        for (auto& p : dirty_coords) {
            int d = dist[0][p.first][p.second];
            if (d == -1) { possible = false; break; }
            cost[0][i] = cost[i][0] = d;
            ++i;
        }
        if (!possible) { cout << "-1\n";  continue; }
        int n = dirty_coords.size();
        rep(i,0,n-2) rep(j,i+1,n-1) {
            int r, c; tie(r, c) = dirty_coords[j];
            cost[i+1][j+1] = cost[j+1][i+1] = dist[i+1][r][c];
        }
        memset(memo, -1, sizeof memo);
        cout << dp((1 << i)-1, 0) << '\n';
    }
    return 0;
}