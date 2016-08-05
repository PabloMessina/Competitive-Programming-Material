/* ============================ */
/* LCA (Lowest Common Ancestor) */
/* ============================ */

// construction: O(2|V| log 2|V|) = O(|V| log |V|)
// query: O(1)

#include <vector>
#include <cstring>
using namespace std;

typedef vector<int> vi;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define irep(i,b,a) for (int i=b; i>=a; --i)

#define MAXN 10000
#define LCA_MAXM 14

int E[2 * MAXN]; // records sequence of visited nodes
int L[2 * MAXN]; // records depth of each visited node
int H[MAXN]; // records index of first ocurrence of node u in E
int idx; // tracks node ocurrences
int lca[2 * MAXN][LCA_MAXM + 1];

int N; // number of nodes
vector<vi> g; // tree graph

// get highest exponent e such that 2^e <= x
inline int lastBitIndex(int x) {
  int i = 0;
  while (x) x >>= 1, ++i;
  return i-1;
}

void dfs(int u, int depth) {
  H[u] = idx; // index of first u's ocurrence
  E[idx] = u; // record node ocurrence
  L[idx++] = depth; // record depth
  for (int v : g[u])
    if (H[v] == -1) {
      dfs(v, depth + 1); // backtrack
      E[idx] = u; // new ocurrence of u
      L[idx++] = depth;
    }
}

void dfs_start() {
  idx = 0;
  memset(H, -1, sizeof(H[0]) * N);
  dfs(0, 0);
}

void buildLCA(int n) {
  int m = lastBitIndex(n);
  rep(i, 0, n - 1)
    lca[i][0] = i; // base case
  rep(j, 1, m) {
    rep(i, 0, n - (1 << j)) {
      // i ... i + 2 ^ (j-1) - 1
      int i1 = lca[i][j-1];
      // i + 2 ^ (j-1) ... i + 2 ^ j  - 1
      int i2 = lca[i + (1 << (j-1))][j-1];
      // choose index with minimum level
      lca[i][j] = (L[i1] < L[i2] ? i1 : i2);
    }
  }
}

int findLCA(int u, int v) {
  // get ocurrence indexes in increasing order
  int l, r;
  if (H[u] < H[v])
    l = H[u], r = H[v];
  else
    l = H[v], r = H[u];
  // get node with minimum level within [l .. r] in O(1)
  int len = r -  l + 1;
  int m = lastBitIndex(len);
  int i1 = lca[l][m];
  int i2 = lca[r - ((1 << m) - 1)][m];
  return L[i1] < L[i2] ? E[i1] : E[i2];
}

inline int getDist(int u, int v) {
  return L[H[u]] + L[H[v]] - 2 * L[H[findLCA(u,v)]];
}