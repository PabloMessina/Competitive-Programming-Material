// tags: LCA, centroid decomposition, segment trees
// problem: http://main.edu.pl/en/archive/pa/2013/pod
// Note: solution it's not working :(

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 500000
#define MAXLOG 20
#define INF 1000000000
typedef vector<int> vi;

int n;
vector<vi> g;

inline int log2(int x) {
  return sizeof(x) * 8 - __builtin_clz(x) - 1;
}

// -----------
// LCA

int E[2 * MAXN];
int L[2 * MAXN];
int H[MAXN];
int idx;
int rmq[2 * MAXN][MAXLOG+1];

void dfs_lca(int u, int l) {
  E[idx] = u;
  L[idx] = l;
  H[u] = idx++;
  for (int i = 0; i < g[u].size(); ++i) {
    int v = g[u][i];
    if (H[v] == -1) {
      dfs_lca(v, l+1);
      E[idx] = u;
      L[idx++] = l;
    }
  }
}

void init_lca() {
  memset(H, -1, sizeof(H[0]) * n);
  idx = 0;
  dfs_lca(0, 0);
  int nn = idx;
  int k = log2(nn);
  rep(i,0,nn-1)
    rmq[i][0] = i;
  rep(j,1,k) {
    rep(i, 0, nn - (1 << j)) {
      int i1 = rmq[i][j-1];
      int i2 = rmq[i + (1 << (j-1))][j-1];
      rmq[i][j] = (L[i1] < L[i2] ? i1 : i2);
    }
  }
}

int LCA(int u, int v) {
  int l, r;
  if (H[u] < H[v])
    l = H[u], r = H[v];
  else
    l = H[v], r = H[u];
  int k = log2(r - l + 1);
  int i1 = rmq[l][k];
  int i2 = rmq[r - (1 << k) + 1][k];
  return L[i1] < L[i2] ? E[i1] : E[i2];
}

int dist(int u, int v) {
  return L[H[u]] + L[H[v]] - 2 * L[H[LCA(u,v)]];
}

// ------------------------
// Centroid Decomposition

vector<vi> cg;
int cg_root;
bool removed[MAXN];
int desc[MAXN];
int cpar[MAXN];

int dfs_count(int u, int p) {
  int count = 1;
  for (int i = 0; i < g[u].size(); ++i) {
    int v = g[u][i];
    if (v != p && !removed[v])
      count += dfs_count(v, u);
  }
  return desc[u] = count;
}

int dfs_cent(int u, int p, int lim) {
  for (int i = 0; i < g[u].size(); ++i) {
    int v = g[u][i];
    if (v != p && !removed[v] && desc[v] > lim)
      return dfs_cent(v, u, lim);
  }
  return u;
}

int centroid(int u) {
  dfs_count(u, -1);
  return dfs_cent(u, -1, desc[u] / 2);
}

void decomp() {
  memset (removed, 0, sizeof(removed[0]) * n);
  cg.assign(n, vi());
  int c = centroid(0);
  removed[c] = true;
  cpar[c] = -1;
  cg_root = c;
  queue<int> q; q.push(c);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int i = 0; i < g[u].size(); ++i) {
      int v = g[u][i];
      if (!removed[v]) {
        c = centroid(v);
        cpar[c] = u;
        cg[u].push_back(c);
        removed[c] = true;
        q.push(c);
      }
    }
  }
}

// -----------------
// Segment Trees

int in[MAXN];
int out[MAXN];
int nodes[MAXN];
void dfs_tour(int u) {
  nodes[idx] = u;
  in[u] = idx++;
  for (int i = 0; i < cg[u].size(); ++i)
    dfs_tour(cg[u][i]);
  out[u] = idx - 1;
}
vi array[MAXN];
vi st[MAXN];
vi stindex[MAXN];

inline int left(int x) { return x * 2; }
inline int right(int x) { return x * 2 + 1; }

int get_max_i(int i1, int i2, int u) {
  if (i1 == -1) return i2;
  if (i2 == -1) return i1;
  int d1 = array[u][i1];
  int d2 = array[u][i2];
  int n1 = nodes[in[u] + i1];
  int n2 = nodes[in[u] + i2];
  return (d1 > d2 || (d1 == d2 && n1 > n2))  ? i1 : i2;
}

inline int get_max_child_i(int p, int u) {
  int i1 = st[u][left(p)];
  int i2 = st[u][right(p)];
  return get_max_i(i1, i2, u);
}

void build_st(int p, int L, int R, int u) {
  if (L == R) {
    st[u][p] = L;
    stindex[u][L] = p;
  } else {
    build_st(left(p), L, (L+R)/2, u);
    build_st(right(p), (L+R)/2 + 1, R, u);
    st[u][p] = get_max_child_i(p, u);
  }
}

void update_point(int i, int val, int u) {
  array[u][i] = val;
  int p = (stindex[u][i] / 2);
  while (p) {
    st[u][p] = get_max_child_i(p, u);
    p /= 2;
  }
}

int query_max(int p, int L, int R, int i, int j, int u) {
  if (i > R || j < L) return -1;
  if (i <= L && R <= j) return st[u][p];
  int i1 = query_max(left(p), L, (L+R)/2, i, j, u);
  int i2 = query_max(right(p), (L+R)/2 + 1, R, i, j, u);
  return get_max_i(i1, i2, u);
}

void build_segment_trees() {
  idx = 0;
  dfs_tour(cg_root);
  rep (u, 0, n-1) {
    int len = out[u] - in[u] + 1;
    // init array
    array[u].resize(len);
    rep(j, in[u], out[u])
      array[u][j - in[u]] = dist(u, nodes[j]);
    // init seg tree
    stindex[u].resize(len);
    st[u].resize(4*len+5);
    build_st(1, 0, len-1, u);
  }
}

// ------------------
// custom queries

int next(int curr) {
  int u = curr;
  int L = 0, R = array[u].size() - 1;
  int i = query_max(1, L, R, L, R, u);
  int maxd = array[u][i];
  int node = nodes[in[u] + i];
  int cp = cpar[u];

  while (cp != -1) {
    R = array[cp].size() - 1;
    int i1 = 0;
    int j1 = in[u] - in[cp] - 1;
    int i2 = out[u] - in[cp] + 1;
    int j2 = R;
    int q1 = query_max(1, L, R, i1, j1, cp);
    int q2 = query_max(1, L, R, i2, j2, cp);
    i = get_max_i(q1, q2, cp);

    int d = array[cp][i] + dist(curr, cp);
    if (maxd < d) {
      maxd = d;
      node = nodes[in[cp] + i];
    }
    u = cp;
    cp = cpar[cp];
  }
  return node;
}
void remove_node(int u) {
  int c = u;
  while (c != -1) {
    update_point(in[u] - in[c], -INF, c);
    c = cpar[c];
  }
}

// -----------
// Main

int main() {
  scanf("%d", &n);
  // build graph
  g.assign(n, vi());
  rep(i, 2, n) {
    int a,b; scanf("%d%d",&a,&b); --a,--b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  // preprocess for LCA
  init_lca();
  // centroid decomposition
  decomp();
  // seg trees
  build_segment_trees();
  // generate answer
  int curr = 0;
  remove_node(curr);
  printf("1");
  rep (i, 2, n) {
    curr = next(curr);
    remove_node(curr);
    printf(" %d", curr+1);
  }
  puts("");
  return 0;
}