//#######################################
//################ BFS ##################
//#######################################

#include <queue>
#include <stack>
#include <vector>
#define MAXN 1000
vector<int> adjList[MAXN];
bool visited[MAXN];

void bfs(int root) {
	queue<int> q;
	q.push(root);
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		visited[u] = true;
		for (int i = 0; i < adjList[u].size(); ++i) {
			int v = adjList[u][i];
			if (visited[v])
				continue;
			q.push(v);
		}
	}
}

//-----------------------------------------------
//single source shortest paths, edge's cost = 1
//-----------------------------------------------
vi d(V, INF); d[s] = 0; // distance from source s to s is 0
queue<int> q; q.push(s); // start from source
while (!q.empty()) {
	int u = q.front(); q.pop(); // queue: layer by layer!
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		int v = AdjList[u][j]; // for each neighbor of u
		if (d[v] == INF) { // if v.first is unvisited + reachable
			d[v] = d[u] + 1; // make d[v.first] != INF to flag it
			q.push(v); // enqueue v.first for the next iteration
		}
	} 
}

