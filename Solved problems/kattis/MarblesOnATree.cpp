#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 10000

typedef vector<int> vi;

int N;
vector<vi> g;
int marb[MAXN];

int tot;
int dfs(int u, int p) {
  int c = marb[u];
  for (int v : g[u])
    if (v != p)
      c += dfs(v, u);
  tot += abs(c - 1);
  return c - 1;
}

int main() {
  while (true) {
    scanf("%d", &N);
    if (N == 0)
      break;

    g.assign(N, vi());

    rep(i,1,N) {
      int u, m, d;
      scanf("%d%d%d", &u, &m, &d); --u;
      marb[u] = m;
      while(d--) {
        int v; scanf("%d", &v); --v;
        g[u].push_back(v);
        g[v].push_back(u);
      }
    }

    tot = 0;
    dfs(0, -1);
    printf("%d\n", tot);
  }
  return 0;
}