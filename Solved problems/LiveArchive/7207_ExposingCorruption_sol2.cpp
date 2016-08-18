// tags: BFS, preprocessing, DP, bottom-up, Knapsack
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXN 200
#define MAXB 10000

typedef vector<int> vi;

int D, P, R, B;
int price[MAXN];
int party[MAXN];
vector<vi> g;

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
  // first item
  memset(memo, 0, sizeof memo);
  if (gain[0][p] > 0) {
    rep (b, weight[0], B) {
      memo[b] = gain[0][p];
    }
  }
  // other items
  rep (i, 1, CN-1) {
    if (gain[i][p] > 0) {
      invrep(b, B, weight[i]) {
        memo[b] = max(memo[b], gain[i][p] + memo[b - weight[i]]);
      }
    }
  }
  return memo[B];
}

int main() {
  while(scanf("%d%d%d%d", &D, &P, &R, &B) == 4) {

    g.assign(D+P, vi());

    rep(i, 0, D-1) {
      scanf("%d", &price[i]);
      party[i] = 0;
    }
    rep(i, 0, P-1) {
      scanf("%d", &price[i+D]);
      party[i+D] = 1;
    }
    rep(i,1,R) {
      int x, y; scanf("%d%d", &x,&y); --x, --y;
      g[x].push_back(D+y);
      g[D+y].push_back(x);
    }
    //
    memset(vis, 0, sizeof vis);
    idx = 0;
    for (int i = 0, n = D+P; i < n; ++i) {
      if (!vis[i]) {
        bfs(i); idx++;
      }
    }
    CN = idx;
    //
    printf("%d %d\n", D + dp(0), P + dp(1));
  }
  return 0;
}