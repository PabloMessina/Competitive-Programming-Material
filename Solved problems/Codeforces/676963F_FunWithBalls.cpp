// tags: backtracking, BFS, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N;
vector<int> K;
int state[400][400];
int xmid = 200;
int vis[400][400];
int vis_id = 1;
vector<pair<int,int>> balls;
int dirs[6][2] = {{-1, 0}, {1, 0}, {0, 1}, {-1, 1}, {0, -1}, {1, -1}};

int search(int i, int l, int r, int h) {
    if (i == N) {
        int ans = 0;
        for (auto& b : balls) {
            int x = b.first, y = b.second;
            if (vis[x][y] == vis_id) continue;
            vis[x][y] = vis_id;
            queue<pair<int,int>> q;
            q.emplace(x, y);
            int count = 1;
            int color = state[x][y];
            while (!q.empty()) {
                auto p = q.front(); q.pop();
                int x = p.first, y = p.second;
                rep(j,0,6) {
                    int dx = dirs[j][0], dy = dirs[j][1];
                    int xx = x + dx, yy = y + dy;
                    if (xx < 0 or xx >= 400 or yy < 0 or yy >= 400) continue;
                    if (vis[xx][yy] == vis_id) continue;
                    if (state[xx][yy] != color) continue;
                    vis[xx][yy] = vis_id;
                    q.emplace(xx, yy);
                    count++;
                }
            }
            ans = max(ans, count);
        }
        vis_id++;
        return ans;
    }
    int ans = 0;
    int num_balls_before = balls.size();
    // expand left side
    int x = l-1, y = 0;
    int j = i;
    rep(k,0,h+1) {
        state[x][y] = K[j];
        balls.eb(x, y);
        y++;
        j++;
        if (j == N) break;
    }
    ans = max(ans, search(j, l-1, r, h+1));
    while (balls.size() > num_balls_before) {
        auto b = balls.back(); balls.pop_back();
        state[b.first][b.second] = 0;
    }
    // expand right side
    x = r+1, y = 0;
    j = i;
    rep(k,0,h+1) {
        state[x][y] = K[j];
        balls.eb(x, y);
        x--;
        y++;
        j++;
        if (j == N) break;
    }
    ans = max(ans, search(j, l, r+1, h+1));
    while (balls.size() > num_balls_before) {
        auto b = balls.back(); balls.pop_back();
        state[b.first][b.second] = 0;
    }
    return ans;
}

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    K.resize(N);
    rep(i,0,N) cin >> K[i];
    memset(state, 0, sizeof(state));
    memset(vis, 0, sizeof(vis));
    state[xmid][0] = K[0];
    balls.eb(xmid, 0);
    cout << search(1, xmid, xmid, 1) << '\n';
    return 0;
}