#include <bits/stdc++.h>
#include <tr1/unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 100
typedef long long int ll;
typedef pair<int,int> pii;
typedef tr1::unordered_set<int> useti;

int n;
int cost[MAXN+1];
int mincost[MAXN+1][MAXN+1];
vector<vector<int>> g;
useti restr[MAXN+1][MAXN+1];

struct triple { int u, p, cost; };


int bfs() {
  queue<triple> q;
  q.push({1, 0, cost[1]});
  mincost[1][0] = cost[1];
  while(!q.empty()) {
    triple t = q.front(); q.pop();
    for (int v: g[t.u]) {
      if (restr[t.u][v].count(t.p) > 0)
        continue;

      int c = t.cost + cost[v];
      if (mincost[v][t.u] == -1 || mincost[v][t.u] > c) {
        mincost[v][t.u] = c;
        q.push({ v, t.u, c});
      }

    }
  }

  int ans = -1;
  rep(i,1,n) {
    if (mincost[n][i] != -1) {
      ans = (ans == -1 ? mincost[n][i] : min(ans, mincost[n][i]));
    }
  }
  return ans;
}


int main() {
  scanf("%d", &n);
  g.assign(n+1, vector<int>());
  rep(i,1,n) {
    int m, t; scanf("%d%d", &m, &t);
    cost[i] = t;
    rep(j,1,m) {
      int s, x; scanf("%d%d", &s, &x);
      g[i].push_back(x);
      rep(k,1,s) {
        int r; scanf("%d", &r);
        restr[i][x].insert(r);
      }
    }
  }

  memset(mincost, -1, sizeof mincost);
  int ans = bfs();
  if (ans == -1)
    puts("impossible");
  else
    printf("%d\n", ans);

  return 0;
}