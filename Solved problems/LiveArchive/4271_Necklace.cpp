#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <queue>
using namespace std;
#define FOR(i,a,b) for(int i = a; i <= b; ++i)

typedef pair<int,int> ii;
typedef vector<int> vi;

int N,M,S,T;
vector<set<int>> graph;
map<ii, int> edgeCounts;
vi depth;
vi low;
vector<ii> cutEdges;
bool foundT;

void dfs(int u, int t) {
  depth[u] = t;
  low[u] = t;
  for(int v : graph[u]) {
    if (v == T) foundT = true;
    if (depth[v] != -1) {
      if (depth[v] < t) { // back edge
        low[u] = min(low[u], depth[v]);
      }
    } else {
      dfs(v, t + 1);
      if (low[v] >= t && edgeCounts[{u,v}] < 2)
        cutEdges.push_back({u,v});
      else
        low[u] = min(low[u], low[v]);
    }
  }
}

int main() {
  int _case = 1;
  begin:
  while (scanf("%d %d", &N, &M) && N && M) {
    // generate graph
    graph.assign(N, set<int>());
    edgeCounts.clear();
    FOR(i,1,M) {
      int a, b;
      scanf("%d %d", &a, &b);
      a--; b--;
      graph[a].insert(b);
      graph[b].insert(a);
      ii ab = {a,b};
      ii ba = {b,a};
      if (edgeCounts.find(ab) == edgeCounts.end()) {
        edgeCounts[ab] = 1;
        edgeCounts[ba] = 1;
      } else {
        edgeCounts[ab]++;
        edgeCounts[ba]++;
      }
    }
    scanf("%d %d",&S, &T);
    S--; T--;
    // dfs
    depth.assign(N,-1);
    low.resize(N);
    cutEdges.clear();
    foundT = false;
    dfs(S,0);
    if (!foundT) {
      printf("Case %d: NO\n", _case++);
      goto begin;
    }
    // remove cut edges
    for (ii& e : cutEdges) {
      graph[e.first].erase(e.second);
      graph[e.second].erase(e.first);
    }
    // check conectivity
    queue<int> q;
    q.push(S);
    vector<bool> visited(N, false);
    visited[S] = true;
    foundT = false;
    while(!q.empty()) {
      int u = q.front(); q.pop();
      if (u == T) {
        foundT = true;
        break;
      }
      for (int v : graph[u]) {
        if (visited[v]) continue;
        visited[v] = true;
        q.push(v);
      }
    }
    if (foundT) printf("Case %d: YES\n", _case);
    else printf("Case %d: NO\n", _case);
    _case++;
  }
  return 0;
}