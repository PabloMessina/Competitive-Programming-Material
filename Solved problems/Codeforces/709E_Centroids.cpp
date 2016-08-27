// tags: DFS, trees, DP, parent-child info propagation

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 400000
typedef vector<int> vi;

int n;
vector<vi> g;
int siz[MAXN];
int maxChild[MAXN];
int submax1[MAXN];
int submax2[MAXN];
int ans[MAXN];

void dfs1(int u, int p) {
  siz[u] = 1;
  maxChild[u] = -2;
  submax1[u] = 0;
  submax2[u] = 0;

  for (int v : g[u]) {
    if (v == p) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] <= n/2) {
      if (siz[v] > submax1[u]) {
        maxChild[u] = v;
        submax2[u] = submax1[u];
        submax1[u] = siz[v];
      } else if (siz[v] > submax2[u]) {
        submax2[u] = siz[v];
      }
    } else {
      if (submax1[v] > submax1[u]) {
        maxChild[u] = v;
        submax2[u] = submax1[u];
        submax1[u] = submax1[v];
      } else if (submax1[v] > submax2[u]) {
        submax2[u] = submax1[v];
      }
    }
  }
}

void dfs2(int u, int p, int pmax) {
  ans[u] = 1;
  for (int v : g[u]) {
    if (v == p) {
      if (n - siz[u] > n/2) {
        ans[u] = (n - siz[u] - pmax > n/2 ? 0 : 1);
        break;
      }
    } else {
      if (siz[v] > n/2) {
        ans[u] = (siz[v] - submax1[v] > n/2 ? 0 : 1);
        break;
      }
    }
  }

  for (int v : g[u]) {
    if (v == p) continue;
    int tmp;
    if (n - siz[v] <= n/2) {
      tmp = n - siz[v];
    } else {
      if (v == maxChild[u]) {
        tmp = max(pmax, submax2[u]);
      } else {
        tmp = max(pmax, submax1[u]);
      }
    }
    dfs2(v, u, tmp);
  }
}

int main() {
  scanf("%d", &n);
  g.assign(n, vi());
  rep(i,2,n) {
    int u,v; scanf("%d%d", &u, &v); --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }
  dfs1(0, -2);
  dfs2(0, -2, 0);
  rep (i,0,n-1) {
    if (i) printf(" %d", ans[i]);
    else printf("%d", ans[i]);
  }
  return 0;
}