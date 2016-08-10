/* ====================== */
/* Centroid Decomposition */
/* ====================== */

// construction: O(n log n)
// query: O(log n)

#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#define MAXN 100000
typedef vector<int> vi;

vector<vi> g; // graph
vector<vi> cg; // centroid graph
int N; // num of nodes
bool removed[MAXN]; // nodes removed from tree
int desc[MAXN]; // num of descendants
int cpar[MAXN]; // centroid parent

// count descendants
int dfs_count(int u, int p) {
  int count = 1;
  for (int v : g[u])
    if (v != p && !removed[v])
      count += dfs_count(v, u);
  return desc[u] = count;
}

// recursive search of centroid
int dfs_cent(int u, int p, int lim) {
  for (int v : g[u])
    if (v != p && !removed[v] && desc[v] > lim)
      return dfs_cent(v, u, lim);
  return u;
}

// find centroid of u's subtree
int centroid(int u) {
  dfs_count(u, -1);
  return dfs_cent(u, -1, desc[u] / 2);
}

// perform centroid decomposition
void decomp() {
  memset(removed, 0, sizeof(removed[0]) * N);  
  cg.assign(N, vi());
  int c = centroid(0);
  cpar[c] = -1;
  removed[c] = true;
  queue<int> q; q.push(c);
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (!removed[v]) {
        c = centroid(v);
        cpar[c] = u; // set parent of c to u
        cg[u].push_back(c); // add edge (u -> c)
        removed[c] = true;
        q.push(c);        
      }
    }
  }
}