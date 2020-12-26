// tags: BFS, preprocessing, DP, bottom-up, Knapsack
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
const int MAXN = 200;
const int MAXB = 10000;
int D, P, R, B;
int price[MAXN];
int party[MAXN];
vector<vector<int>> g;
int CN;
int idx;
int gain[MAXN][2];
int weight[MAXN];
bool vis[MAXN];

void bfs(int s) {
    queue<int> q; q.push(s);
    gain[idx][party[s]] = -1;
    gain[idx][1-party[s]] = 1;
    weight[idx] = price[s];
    vis[s] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (!vis[v]) {
                vis[v] = true;
                q.push(v);
                weight[idx] += price[v];
                gain[idx][party[v]]--;
                gain[idx][1-party[v]]++;
            }
        }
    }
}

int memo[MAXB+1];

int dp(int p) {
    memset(memo, 0, sizeof(memo[0]) * (B+1));
    rep(i,0,CN) {
        if (gain[i][p] > 0) {
            invrep(b, B, weight[i]) {
                memo[b] = max(memo[b], gain[i][p] + memo[b - weight[i]]);
            }
        }
    }
    return memo[B];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while(cin >> D >> P >> R >> B) {
        int n = D+P;
        g.assign(n, vector<int>());
        rep(i,0,D) { cin >> price[i]; party[i] = 0; }
        rep(i,0,P) { cin >> price[i+D]; party[i+D] = 1; }
        rep(_,0,R) {
            int x, y; cin >> x >> y; --x, --y;
            g[x].push_back(D+y);
            g[D+y].push_back(x);
        }
        memset(vis, 0, sizeof(vis[0]) * n);
        idx = 0;
        rep(i,0,n) if (!vis[i]) bfs(i), idx++;
        CN = idx;
        cout << D + dp(0) << " " << P + dp(1) << '\n';
    }
    return 0;
}