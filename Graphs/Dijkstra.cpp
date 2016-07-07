/* ========== */
/*  DIJKSTRA  */
/* ========== */
// complexity: (|E| + |V|) * log |V|

/* pseudo code */

function Dijkstra(Graph, source):
    // Initialization
    dist[source] ← 0 
    create vertex set Q
    for each vertex v in Graph:           
        if v ≠ source
            dist[v] ← INFINITY // Unknown distance from source to v
            prev[v] ← UNDEFINED // Predecessor of v
        Q.add_with_priority(v, dist[v])
    // The main loop
    while Q is not empty: 
        u ← Q.extract_min() // Remove and return best vertex
        for each neighbor v of u:    // only v that is still in Q
            alt = dist[u] + length(u, v) 
            if alt < dist[v]
                dist[v] ← alt
                prev[v] ← u
                Q.decrease_priority(v, alt)
    return dist[], prev[]

/* code */

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)
#define INF 1e9

typedef vector<int> vi;
typedef vector<vi> vii;

struct Edge {
  int u;
  int v;
  int w;
};

struct Pair {
  int node;
  int dist;
  bool operator<(const Pair& p) {
    return w > p.w;
  }
};

int main() {
  int V, E, s;
  scanf("%d %d %d", &V, &E, &s);
  /* initialization */
  vector<vector<Edge>> adjList(V);
  FOR(i,0,E) {
    Edge e;
    scanf("%d %d %d",&e.u,&e.v,&e.w);
    adjList[e.u].push_back(e);
  }
  vi dist(V,INF);
  vi parent(V,-1);
  dist[s] = 0;
  priority_queue<Pair> pq;
  pq.push({s,0});
  /* routine */
  while (!pq.empty()) {
    Pair top = pq.top(); pq.pop();
    int u = top.node;
    int d = top.dist;
    if (d > dist[u]) continue; // skip outdated improvements
    FOR(i,0,adjList[u].size()) {
      Edge& e = adjList[u][i];
      int alt = d + e.w;
      if (alt < dist[e.v]) {
        dist[e.v] = alt;
        parent[e.v] = u;
        pq.push({e.v,alt});
      }
    }
  }
  return 0;
}