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

// METHOD 1: remember depth per node

vi d(V, INF); d[s] = 0; // distance from source s to s is 0
queue<int> q; q.push(s); // start from source
while (!q.empty()) {
	int u = q.front(); q.pop(); // queue: layer by layer!
	for (int j = 0; j < (int)AdjList[u].size(); j++) {
		int v = AdjList[u][j]; // for each neighbor of u
		if (d[v] == INF) { // if v is unvisited + reachable
			d[v] = d[u] + 1; // make d[v] != INF to flag it
			q.push(v); // enqueue v for the next iteration
		}
	} 
}

// METHOD 2: remember frontier's depth by swapping 2 queues

vector<queue<int> > qs(2);
queue<int>* currq = &qs[0];
queue<int>* nextq = &qs[1];
currq->push(s);
vi d(V, INF);
int qindex = 0;

int pathLength = 0;

while (!currq.empty()) {
	pathLength++;
	while (!currq.empty()) {
		int u = currq->front(); currq->pop();

		for (int j = 0; j < (int)AdjList[u].size(); j++) {
			int v = AdjList[u][j]; // for each neighbor of u	
			if (d[v] == INF) { // if v is unvisited + reachable
				visited[v] = 1; // flag it
				nextq.push(v); // enqueue for next layer
			}
		}
	}
	// swap queues
	qindex = 1 - qindex;
	currq = &qs[qindex];
	nextq = &qs[1 - qindex];
}