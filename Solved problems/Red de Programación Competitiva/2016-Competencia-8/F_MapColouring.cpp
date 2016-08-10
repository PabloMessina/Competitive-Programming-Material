// tags: backtracking, pruning

#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef vector<int> vi;

int C, B;
vector<vi> g;
int banned[16][4];
int color[16];
int K;

bool colorate(int u) {

  if (u == C) return true;

  rep(c, 0, K-1) {

    if (banned[u][c] == 0) { // not banned

      // check color is not used by neighbors
      bool used = false;
      for (int v : g[u]) {
        if (color[v] == c) {
          used = true;
          break;
        }
      }
      if (used) continue;

      // assign color
      color[u] = c;

      // ban color in neighbors
      for (int v : g[u])
        banned[v][c]++;

      // recursive call
      if (colorate(u+1)) return true;

      // backtrack
      for (int v : g[u])
        banned[v][c]--;
      color[u] = -1;
    }
  }

  return false;
}

int main() {
  int T; scanf("%d", &T);
  while (T--) {
    scanf("%d%d",&C,&B);
    g.assign(C, vi());

    // build graph
    rep (i, 1, B) {
      int x, y; scanf("%d%d",&x,&y);
      g[x].push_back(y);
      g[y].push_back(x);
    }

    // backtracking
    bool found = false;
    for (K = 1; K <= 4; ++K) {
      memset(banned, 0, sizeof banned);
      memset(color, -1, sizeof color);
      if (colorate(0)) {
        found = true; break;
      }
    }
    if (found) printf("%d\n", K);
    else puts("many");
  }
  return 0;
}