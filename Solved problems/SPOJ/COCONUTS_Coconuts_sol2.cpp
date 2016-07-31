// tags: dinic, max-flow, min-cut
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

int n, m;
int s, t;
int res[MAXV][MAXV];
int d[MAXV];
vector<vi> g;

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

int dinic() {
  int mf = 0;
  while (bfs()) {
    int f;
    while (f = dfs(s, INF)) mf += f; 
  }
  return mf;
}

void add_edge(int u, int v, int c) {
  g[u].push_back(v);
  res[u][v] = c;
}

void init() {
  // reset structures
  s = n, t = n + 1;
  g.assign(t + 1, vi());
  memset(res, 0, sizeof res);
  // build graph
  FOR(i,0,n-1) {
    int p; scanf("%d", &p);
    if (p) add_edge(s, i, 1);
    else add_edge(i, t, 1);
  }
  FOR(i,1,m) {
    int u, v; scanf("%d%d",&u,&v); --u, --v;
    add_edge(u, v, 1);
    add_edge(v, u, 1);
  }
}

int main() {
  while (scanf("%d%d", &n, &m), n || m) {
    init();
    printf("%d\n", dinic());
  }
  return 0;
}