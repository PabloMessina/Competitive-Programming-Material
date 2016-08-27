// DFS, loop detection, pruning

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 100

typedef vector<int> vi;
typedef pair<int,int> pii;

int n;
vector<vi> g;
int energy[MAXN];
int target;

enum Flag { UNVISITED, STACK, VISITED };
struct State { int energy, flag; };
State state[MAXN];

bool dfs(int u, int e) {
  if (u == target)
    return true;

  if (e != INT_MAX) {
    e += energy[u];
    if (e <= 0)
      return false;
  }

  if (state[u].flag == STACK) {
    if (state[u].energy >= e)
      return false;
    else {
      e = INT_MAX;
    }
  } else if (state[u].flag == VISITED) {
    if (state[u].energy >= e)
      return false;
  }

  state[u].flag = STACK;
  state[u].energy = e;

  for (int v : g[u])
    if (dfs(v, e))
      return true;

  state[u].flag = VISITED;
  return false;
}

int main() {
  while(true) {
    scanf("%d", &n);
    if (n==-1) break;

    g.assign(n, vi());

    rep(u,0,n-1) {
      int d; scanf("%d%d", &energy[u], &d);
      rep(j,1,d) {
        int v; scanf("%d", &v); --v;
        g[u].push_back(v);
      }
      state[u].flag = UNVISITED;
      state[u].energy = INT_MIN;
    }
    target = n-1;
    if (dfs(0, 100))
      puts("winnable");
    else
      puts("hopeless");
  }
  return 0;
}