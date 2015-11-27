//#############################################
//################ DFS - BFS ##################
//#############################################

#include <queue>
#include <stack>
#include <vector>
#define MAXN 1000
vector<int> adjList[MAXN];
bool visited[MAXN];

void dfs(int root) {
	stack<int> s;
	s.push(root);
	while (!s.empty()) {
		int u = s.top();
		s.pop();
		visited[u] = true;
		for (int i = 0; i < adjList[u].size(); ++i) {
			int v = adjList[u][i];
			if (visited[v])
				continue;
			s.push(v);
		}
	}
}

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