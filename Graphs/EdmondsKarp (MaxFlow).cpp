/* ============== */
/*  Edmonds Karp  */
/* ============== */
// complexity: |V| * |E|^2

#include <algorithm>
#include <bitset>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;

#define INF 1000000000
#define MAX_V 40

int res[MAX_V][MAX_V]; //residual capacities
int mf, f, s, t;
vi p;
vector<vi> AdjList;

void augment(int v, int minEdge) {     // traverse BFS spanning tree from s to t
  if (v == s) { f = minEdge; return; }  // record minEdge in a global variable f
  else if (p[v] != -1) { augment(p[v], min(minEdge, res[p[v]][v])); // recursive
                         res[p[v]][v] -= f; res[v][p[v]] += f; }       // update
}

int main() {
	int V, k, vertex, weight;
	scanf("%d %d %d", &V, &s, &t);

	//initialize AdjList and res
	AdjList.assign(V,vi());
  for (int i = 0; i < V; i++) {
    scanf("%d", &k);
    for (int j = 0; j < k; j++) {
      scanf("%d %d", &vertex, &weight);
      //forward residual capacity
      AdjList[i].push_back(vertex);
      res[i][vertex] = weight;
      //backward residual capacity
      AdjList[vertex].push_back(i);
      res[vertex][i] = 0;
    }
  }

  mf = 0;
  while (1) {

  	//run BFS to find aumenting path
    f = 0;
    bitset<MAX_V> vis; vis[s] = true;
    queue<int> q; q.push(s);
    p.assign(MAX_V, -1); //reset parents
    while (!q.empty()) {
      int u = q.front(); q.pop();
      //if (u == t) break; //not necesary, check goto below
      for (int j = 0; j < (int)AdjList[u].size(); j++) {  // we use AdjList here!
        int v = AdjList[u][j];
        if (res[u][v] > 0 && !vis[v]) {
          vis[v] = true, q.push(v), p[v] = u;
          if(v == t) { //target found!!
          	goto end_bfs;
          }
        }
      }
    }
    end_bfs:
    augment(t, INF);
    if (f == 0) break;
    mf += f;
  }

  printf("%d\n", mf);                              // this is the max flow value

  return 0;
}