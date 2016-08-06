// tags: LCA, LA, level ancestors, jump pointers, 
//       tree diameter, BFS, DFS, sparse tables

#include <cstdio>
#include <vector>
#include <queue>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,b,a) for (int i=b; i>=a; --i)
#define MAXN 20000
#define LCA_MAXJ 16
#define LA_MAXJ 16

typedef vector<int> vi;

int n, q;
vector<vi> g;
int e1, e2;
int dist[MAXN];

int farthestFrom(int s) {
  int farthest = s;
  int maxd = 0;
  memset(dist, -1, sizeof(dist[0]) * n);
  queue<int> q; q.push(s);
  dist[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
        if (dist[v] > maxd) {
          maxd = dist[v];
          farthest = v;
        }
      }
    }
  }
  return farthest;
}

inline int log2(int x) {
  int i = 0;
  while (x) x >>= 1, ++i;
  return i-1;
}

// ========================================
// Lowest Common Ancestor & Level Ancestor

int L[2 * MAXN];
int E[2 * MAXN];
int H[MAXN];
int P[MAXN];
int D[MAXN];
int idx;

// lowest common ancestor
int lca[2 * MAXN][LCA_MAXJ + 1];
// level ancestor
int la[MAXN][LA_MAXJ + 1];

void dfs(int u, int p, int depth) {
  H[u] = idx;
  P[u] = p;
  D[u] = depth;
  E[idx] = u;
  L[idx++] = depth;
  for (int v : g[u])
    if (H[v] == -1) {
      dfs(v, u, depth + 1);
      E[idx] = u;
      L[idx++] = depth;
    }
}

void dfs_start() {
  idx = 0;
  memset(H, -1, sizeof(H[0]) * n);
  dfs(0, -1, 0);
}

void buildLCA(int nn) {
  int mm = log2(nn);
  rep(i, 0, nn - 1)
    lca[i][0] = i;
  rep(j, 1, mm) {
    rep(i, 0, nn - (1 << j)) {
      int i1 = lca[i][j-1];
      int i2 = lca[i + (1 << (j-1))][j-1];
      lca[i][j] = (L[i1] < L[i2] ? i1 : i2);
    }
  }
}

void buildLA(int nn) {
  int mm = log2(nn);
  rep(i, 0, nn - 1) {
    la[i][0] = P[i];
  }
  rep(j, 1, mm) {
    rep(i, 0, nn - 1) {
      int p = la[i][j-1];
      la[i][j] = (p != -1 ? la[p][j-1] : -1);
    }
  }
}

int findLCA(int u, int v) {
  int l, r;
  if (H[u] < H[v])
    l = H[u], r = H[v];
  else
    l = H[v], r = H[u];
  int len = r -  l + 1;
  int m = log2(len);
  int i1 = lca[l][m];
  int i2 = lca[r + 1 - (1 << m)][m];
  return L[i1] < L[i2] ? E[i1] : E[i2];
}

int findLA(int u, int k) {

  if (k == 0) return u;
  if (D[u] < k) return -1;
  int m = log2(k);
  invrep (j, m, 0) {
    if (k >= (1 << j)) {
      u = la[u][j];
      k -= (1 << j);
      if (k == 0 || u == -1) break;
    }
  }
  return u;
}

inline int getDist(int u, int v) {
  return D[u] + D[v] - 2 * D[findLCA(u,v)];
}

// =============
// MAIN

int main() {
  scanf("%d%d",&n,&q);

  // 0. build graph
  g.assign(n, vi());
  rep(i,1,n-1) {
    int u, v; scanf("%d%d",&u,&v); --u, --v;
    g[u].push_back(v);
    g[v].push_back(u);
  }

  // 1. find diameter's ends
  e1 = farthestFrom(0);
  e2 = farthestFrom(e1);

  // 2. build sparse tables for LCA and LA
  dfs_start();
  buildLCA(idx);
  buildLA(n);

  // 3. answer queries
  rep(i, 1, q) {
    int v, d; scanf("%d%d", &v, &d); --v;

    // check it's reachable
    int f, maxd;
    int d1 = getDist(v, e1);
    int d2 = getDist(v, e2);
    if (d1 > d2)
      f = e1, maxd = d1;
    else
      f = e2, maxd = d2;
    if (d > maxd) { puts("0"); continue; }

    // find lca between f and v
    int lca_fv = findLCA(f, v);

    // answer
    int ans;
    if (D[v] - D[lca_fv] >= d)
      ans = findLA(v, d) + 1;
    else
      ans = findLA(f, D[f] + D[v] - 2 * D[lca_fv] - d) + 1;
    printf("%d\n", ans);
  }
  return 0;
}