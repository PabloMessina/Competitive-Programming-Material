/* ============================ */
/* LCA (Lowest Common Ancestor) */
/* ============================ */
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,b,a) for (int i=b; i>=a; --i)

// -----------------------------------
// METHOD 1: SPARSE TABLE - EULER TOUR
// -----------------------------------
// construction: O(2|V| log 2|V|) = O(|V| log |V|)
// query: O(1)  
// cannot be updated :(


#define MAXN 10000
#define MAXLOG 14

int E[2 * MAXN]; // records sequence of visited nodes
int L[2 * MAXN]; // records level of each visited node
int H[MAXN]; // records index of first ocurrence of node u in E
int idx; // tracks node ocurrences
int rmq[2 * MAXN][MAXLOG + 1];

int N; // number of nodes
vector<vi> g; // tree graph

// get highest exponent e such that 2^e <= x
inline int log2(int x) { return sizeof(x) * 8 - __builtin_clz(x) - 1; }

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

void lca_init() {
  idx = 0;
  memset(H, -1, sizeof(H[0]) * N);
  dfs(0, 0); // euler tour to initialize H, E, L
  int nn = idx; // <-- make sure you use the correct number  
  int m = log2(nn);

  rep(i, 0, nn - 1)
    rmq[i][0] = i; // base case
  rep(j, 1, m) {
    rep(i, 0, nn - (1 << j)) {
      // i ... i + 2 ^ (j-1) - 1
      int i1 = rmq[i][j-1];
      // i + 2 ^ (j-1) ... i + 2 ^ j  - 1
      int i2 = rmq[i + (1 << (j-1))][j-1];
      // choose index with minimum level
      rmq[i][j] = (L[i1] < L[i2] ? i1 : i2);
    }
  }
}

int LCA(int u, int v) {
  // get ocurrence indexes in increasing order
  int l, r;
  if (H[u] < H[v])
    l = H[u], r = H[v];
  else
    l = H[v], r = H[u];
  // get node with minimum level within [l .. r] in O(1)
  int len = r -  l + 1;
  int m = log2(len);
  int i1 = rmq[l][m];
  int i2 = rmq[r - ((1 << m) - 1)][m];
  return L[i1] < L[i2] ? E[i1] : E[i2];
}

inline int dist(int u, int v) {
  // make sure you use H to retrieve the indexes of
  // u and v within the Euler Tour sequence before
  // using L
  return L[H[u]] + L[H[v]] - 2 * L[H[LCA(u,v)]];
}

// ---------------------------------------
// METHOD 2: SPARSE TABLE - JUMP POINTERS
// ----------------------------------------
// construction: O(|V| log |V|)
// query: O(log|V|)
// can be updated: tree can receive new nodes :)

#define MAXN 1000000
#define MAXLOG 20

int P[MAXN][MAXLOG+1]; // level ancestor table
int L[MAXN]; // levels
int N; // num of nodes
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

void init() {
  memset(P, -1, sizeof P);
  memset(L, -1, sizeof L);
  dfs(root, -1, 0);
  rep(j, 1, MAXLOG) {
    rep (i, 0, N-1) {
      // i's 2^j th ancestor is
      // i's 2^(j-1) th ancestor's 2^(j-1) th ancestor
      int p = P[i][j-1];
      if (p != -1) P[i][j] = P[a][j-1];
    }
  }
}

int log2(int x) {
  int i = 0;
  while (x) x>>=1, i++;
  return i-1;
}

int LCA(int u, int v) {
  if (level[u] < level[v]) swap(u, v);
  // raise lowest to same level
  int diff = level[u] - level[v];
  while (diff) {
    int j = log2(diff);
    u = P[u][j];
    diff -= (1 << j);
  }
  if (u == v) return u; // same node, we are done
  // raise u and v to their highest ancestors below
  // the LCA
  invrep (j, MAXLOG, 0)
    // if there are 2^j th ancestors for u and v
    // and they are not the same,
    // then they can be raised and still be below the LCA
    if (P[u][j] != -1 && P[u][j] != P[v][j])
      u = P[u][j], v = P[v][j];
  // the direct parent of u (or v) is lca(u,v)
  return P[u][0];
}

int dist(int u, int v) {
  return L[u] + L[v] - 2 * L[LCA(u,v)];
}

int add_child(int u, int v) {
  // add to graph
  g[u].push_back(v);
  // update level
  L[v] = L[u] + 1;
  // update ancestors
  P[v][0] = u;
  rep (j, 1, MAXLOG){
    P[v][j] = P[P[v][j-1]][j-1];
    if (P[v][j] == -1) break;
  }
}