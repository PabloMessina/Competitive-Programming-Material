/* ========================== */
/* BFS (Breadth First Search) */
/* ========================== */

#include <queue>
#include <stack>
#include <vector>
#define MAXN 1000

typedef vector<int> vi;
vector<vi> g; // graph
vi depth; // bfs depth per node
int N; // num of nodes

void bfs(int s) {
	queue<int> q; q.push(s);
	depth.assign(N,-1);
	depth[s] = 0;
	while (!q.empty()) {
		int u = q.front(); q.pop();
		for (int v : g[u]) {
			if (depth[v] == -1) {
				depth[v] = depth[u] + 1;
				q.push(v);
			}
		}
	}
}


// ==========================
// Find Tree's Diameter Ends
// ==========================

#include <cstring>
#include <queue>
#include <vector>
using namespace std;

int dist[MAXN];
vector<vi> g;

int farthestFrom(int s) {
  int farthest = s;
  int maxd = 0;
  memset(dist, -1, sizeof(dist[0]) * n);
  queue<int> q; q.push(s);
  dist[s] = 0;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (dist[v] == -1) {
        dist[v] = dist[u] + 1;
        q.push(v);
        if (dist[v] > maxd) {
          maxd = dist[v];
          farthest = v;
        }
      }
    }
  }
  return farthest;
}

void findDiameter(int& e1, int& e2) {
	e1 = farthestFrom(0);
	e2 = farthestFrom(e1);
}
