/* ======= */
/*  DINIC  */
/* ======= */
// complexity: |E| * |V|^2

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define MAXV 310
#define INF 1000000000
typedef vector<int> vi;

int s, t; // source, target
int res[MAXV][MAXV]; // residual graph
int d[MAXV]; // distances
vector<vi> g; // graph

/* find blocking flow graph */
bool bfs() {
  memset(d, -1, sizeof(d[0]) * (t+1));
  queue<int> q; q.push(s); d[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (res[u][v] > 0 && d[v] == -1) {
        d[v] = d[u] + 1;
        q.push(v);
      }
    }
  }
  return d[t] != -1;
}
/* find augmenting path */
int dfs (int u, int f) {
  if (u == t) return f;
  for (int v : g[u]) {
    if (res[u][v] > 0 && d[v] == d[u] + 1) {
      int r = dfs(v, min(f, res[u][v]));
      if (r) {
        res[u][v] -= r;
        res[v][u] += r;
        return r;
      }
    }
  }
  return 0;
}
/* dinic's global function */
int dinic() {
  int mf = 0;
  while (bfs()) {
    int f;
    while (f = dfs(s, INF))
      mf += f;
  }
}