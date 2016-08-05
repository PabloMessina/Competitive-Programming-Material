/* =========================== */
/* LA (Level Ancestor Problem) */
/* =========================== */

#include <vector>
using namespace std;

typedef vector<int> vi;

#define rep (i,a,b) for(int i=a; i<=b; ++i)
#define irep(i,b,a) for(int i=b; i>=a; --i)

#define MAXN 10000
#define LA_MAXM 16

int la[LA_MAXM + 1][MAXN]; // level ancestor table
int P[MAXN]; // parent array
int D[MAXN]; // depth array
vector<vi> g; // tree graph

// dfs to record parents and depths
void dfs(int u, int p, int d) {
  P[u] = p; D[u] = d;
  for (int v : g[u])
    if (P[u] == -1)
      dfs(v, u, d + 1);
}

inline int lastBitIndex(int x) {
  int i = 0;
  while (x) x>>=1, i++;
  return i-1;
}

void buildLA(int n) {
  int m = lastBitIndex(n);
  rep(i, 0, n - 1) // base case
    la[0][i] = P[i]; // 2^0 = 1th ancestor
  rep(j, 1, m) {
    rep(i, 0, n - 1) {
      // 2^j th ancestor of i
      // = 2^(j-1) th ancestor of 2^(j-1) th ancestor of i
      int p = la[j-1][i];
      la[j][i] = (p != -1 ? la[j-1][p] : -1);
    }
  }
}

int findLA(int u, int k) {
  if (k == 0) return u; // trivial case
  if (D[u] < k) return -1; // check ancestor exists
  int m = lastBitIndex(k);
  irep (j, m, 0) {
    if (k >= (1 << j)) {
      u = la[j][u]; // u = 2^j th ancestor of u
      k -= (1 << j); // only k - 2^j steps left
      if (k == 0) break; // target reached
    }
  }
  return u;
}