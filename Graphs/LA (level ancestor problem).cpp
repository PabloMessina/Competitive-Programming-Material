/* =========================== */
/* LA (Level Ancestor Problem) */
/* =========================== */

#include <vector>
using namespace std;

typedef vector<int> vi;

#define rep (i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,b,a) for(int i=b; i>=a; --i)

#define MAXN 10000
#define MAXLOG 16

int P[MAXN][MAXLOG + 1]; // level ancestor table
int L[MAXN]; // level array
vector<vi> g; // tree graph
int root; // root of the tree

// dfs to record direct parents and levels
void dfs(int u, int p, int l) {
  P[u][0] = p;
  L[u] = l;
  for (int v : g[u])
    if (L[v] == -1)
      dfs(v, u, l + 1);
}

inline int log2(int x) {
  int i = 0;
  while (x) x>>=1, i++;
  return i-1;
}

void init_la(int n) {
  memset(P, -1, sizeof P);
  memset(L, -1, sizeof L);
  dfs(root, -1, 0);
  // fill sparse table
  int m = log2(n);
  rep(j, 1, m) {
    rep(i, 0, n - 1) {
      // 2^j th ancestor of i
      // = 2^(j-1) th ancestor of 2^(j-1) th ancestor of i
      int p = P[i][j-1];
      if (p != -1) P[i][j] = P[p][j-1];
    }
  }
}

int lev_anc(int u, int k) {
  if (k == 0) return u; // trivial case
  if (L[u] < k) return -1; // check ancestor exists
  invrep(j, log2(k), 0) {
    if (k >= (1 << j)) {
      u = P[u][j]; // u = 2^j th ancestor of u
      k -= (1 << j); // only k - 2^j steps left
      if (k == 0) break; // target reached
    }
  }
  return u;
}