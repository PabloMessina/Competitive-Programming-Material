// tags: centroid decomposition, LCA, sparse table
#include <cstdio>
#include <vector>
#include <cstring>
#include <cmath>
#include <queue>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define INF 1000000000
#define MAXN 100000
#define MAXLOG 20

typedef vector<int> vi;

int n, m;
vector<vi> g; // tree graph

// -------------
// LCA 

int E[2 * MAXN];
int L[2 * MAXN];
int H[MAXN];
int idx;
int rmq[2 * MAXN][MAXLOG + 1];

inline int log2(int x) {
  return sizeof(x) * 8 - __builtin_clz(x) - 1;
}

int dfs_lca(int u, int l) {
  E[idx] = u;
  L[idx] = l;
  H[u] = idx++;
  for (int v : g[u]) {
    if (H[v] == -1) {
      dfs_lca(v, l+1);
      E[idx] = u;
      L[idx++] = l;
    }
  }
}

void init_lca() {
  // euler tour
  memset(H, -1, sizeof(H[0]) * n);
  idx = 0; 
  dfs_lca(0, 0);

  // rmq with sparse table
  int nn = idx; 
  int k = log2(nn);
  rep(i, 0, nn-1)
    rmq[i][0] = i;
  rep(j, 1, k) {
    rep(i, 0, nn - (1 << j)) {
      int i1 = rmq[i][j-1];
      int i2 = rmq[i + (1 << (j-1))][j-1];
      rmq[i][j] = (L[i1]  < L[i2] ? i1 : i2);
    }
  }
}

int LCA(int u, int v) {
  int l, r;
  if (H[u] < H[v])
    l = H[u], r = H[v];
  else
    l = H[v], r = H[u];
  int len = r - l + 1;
  int j = log2(len);
  int i1 = rmq[l][j];
  int i2 = rmq[r - (1 << j) + 1][j];
  return L[i1] < L[i2] ? E[i1] : E[i2];
}

inline int dist(int u, int v) {
  return L[H[u]] + L[H[v]] - 2 * L[H[LCA(u,v)]];
}

// -----------------------
// centroid decomposition

bool deleted[MAXN];
int children[MAXN];
int cparent[MAXN];

int dfs_dec(int u, int p) {
  int count = 1;
  for (int v : g[u]) {
    if (v == p || deleted[v]) continue;
    count += dfs_dec(v, u);
  }
  return children[u] = count;
}

int centroid(int root) {
  dfs_dec(root, -1);
  int c = root;
  int lim = children[root] / 2;
  int p = -1;
  while (true) {
    bool done = true;
    for (int v : g[c]) {
      if (v == p || deleted[v]) continue;
      if (children[v] > lim) {
        p = c;
        c = v;
        done = false;
        break;
      }
    }
    if (done) break;
  }
  return c;
}

void centroid_decomp() {
  memset(deleted, 0, sizeof(deleted[0]) * n);  
  int c = centroid(0);
  cparent[c] = -1;
  deleted[c] = true;
  queue<int> q; q.push(c);

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (deleted[v]) continue;
      c = centroid(v);
      cparent[c] = u;
      deleted[c] = true;
      q.push(c);
    }
  }
}

// -------------
// queries

int red_dist[MAXN];

void paint(int u) {
  int c = u;
  while (c != -1) {
    red_dist[c] = min(red_dist[c], dist(c, u));
    c = cparent[c];
  }
}

int query(int u) {
  int mind = INF;
  int c = u;
  while (c != -1) {
    mind = min (mind, red_dist[c] + dist(c, u));
    c = cparent[c];
  }
  return mind;
}

// ---------
// main

int main () {

  scanf("%d%d",&n,&m);

  // build graph
  g.assign(n, vi());
  rep(i,2,n) {
    int a,b; scanf("%d%d",&a,&b); --a, --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }

  // preprocess LCA
  init_lca();

  // centroid decomposition
  centroid_decomp();

  // queries
  rep(i,0,n-1) red_dist[i] = INF;
  paint(0); // paint first node
  rep(i, 1, m) {
    int t, v; scanf("%d%d",&t,&v); --v;
    if (t == 1)
      paint(v);
    else
      printf("%d\n", query(v));
  }
  return 0;
}