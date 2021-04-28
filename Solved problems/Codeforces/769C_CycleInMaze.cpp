// tags: graphs, BFS, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
string board[1005];
int D[1005][1005];
int movr[4] = {1, 0, 0, -1};
int movc[4] = {0, -1, 1, 0};
string moves = "DLRU";
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, k; cin >> n >> m >> k;
    rep(i,0,n) cin >> board[i];
    int sr, sc;
    rep(i,0,n) rep(j,0,m) if (board[i][j] == 'X') sr = i, sc = j;
    memset(D, -1, sizeof D);
    queue<ii> q; q.emplace(sr, sc);
    D[sr][sc] = 0;
    while (q.size()) {
        int r, c; tie(r,c) = q.front(); q.pop();
        rep(i,0,4) {
            int rr = r + movr[i];
            int cc = c + movc[i];
            if (0 <= rr and rr < n and 0 <= cc and cc < m and board[rr][cc] != '*' and D[rr][cc] == -1) {
                D[rr][cc] = D[r][c] + 1;
                q.emplace(rr, cc);
            }
        }
    }
    int r = sr, c = sc;
    string path = "";
    rep(step,1,k+1) {
        bool possible = false;
        rep(i,0,4) {
            int rr = r + movr[i];
            int cc = c + movc[i];
            if (0 <= rr and rr < n and 0 <= cc and cc < m and D[rr][cc] != -1
                    and D[rr][cc] <= k - step) {
                path += moves[i];
                possible = true;
                r = rr, c = cc;
                break;
            }
        }
        if (not possible) break;
    }
    if (path.size() == k and r == sr and c == sc) {
        // assert (r == sr and c == sc);
        cout << path << '\n';
    } else {
        // assert (path.size() == 0);
        cout << "IMPOSSIBLE\n";
    }
    return 0;
}