#include <cstdio>
#include <vector>
#include <set>
#include <stack>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;++i)

typedef vector<int> vi;
typedef pair<int,int> ii;

vi comp_before;
vi comp_after;
vi low;
vi depth;
vi color;
vector<set<int>> g;
stack<ii> s;
vector<ii> banned;
int curr_comp;

int n, m;

void removeComp(bool odd, ii e) {
  while (true) {
    if (odd) banned.push_back(s.top());
    if (s.top() == e) { s.pop(); break; }
    else s.pop();
  }
}

bool dfs(int u, int p, int d) {
  comp_before[u] = curr_comp;
  depth[u] = d;
  low[u] = d;

  bool odd = false;

  for (int v : g[u]) {
    if (v == p) continue;

    if (depth[v] == -1) {

      ii uv(u,v);
      s.push(uv);

      bool v_odd = dfs(v, u, d + 1);

      if ((p == -1) || (low[v] >= depth[u]))// root or articulation point
        removeComp(v_odd, uv);
      else {
        odd = odd or v_odd; // propagate oddness
        low[u] = min(low[u], low[v]);
      }

    } else if (depth[v] < depth[u]) { // back edge
      if ((depth[u] - depth[v]) % 2 == 0) // odd loop
        odd = true;
      s.push({u,v});
      low[u] = min(low[u], depth[v]);
    }
  }

  return odd;
}

void bfs(int s) {
  queue<int> q;
  q.push(s);
  color[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    comp_after[u] = curr_comp;
    for (int v : g[u]) {
      if (color[v] == -1) {
        color[v] = 1 - color[u];
        q.push(v);
      } 
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);

  g.assign(n, set<int>());
  comp_before.resize(n);
  comp_after.assign(n, -1);
  low.resize(n);
  depth.assign(n, -1);
  color.assign(n, -1);
  banned.clear();
  while(!s.empty()) s.pop();

  // build graph
  FOR(i, 1, m) {
    int a, b; scanf("%d%d",&a, &b), --a, --b;
    g[a].insert(b);
    g[b].insert(a);
  }

  // dfs's
  curr_comp = 0;
  FOR(i, 0, n-1)
    if (depth[i] == -1)
      dfs(i, -1, 0), curr_comp++;

  // remove banned edges
  for (auto e : banned) {
    g[e.first].erase(e.second);
    g[e.second].erase(e.first);
  }

  // bfs's
  curr_comp = 0;
  FOR(i, 0, n-1)
    if (color[i] == -1)
      bfs(i), curr_comp++;

  // queries
  int q; scanf("%d", &q);
  while (q--) {
    int a, b; scanf("%d%d",&a,&b), --a, --b;
    if (comp_before[a] != comp_before[b])
      puts("No");
    else if (comp_after[a] != comp_after[b])
      puts("Yes");
    else if (color[a] != color[b])
      puts("Yes");
    else
      puts("No");
  }
  return 0;
}