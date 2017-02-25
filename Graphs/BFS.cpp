#define MAXN 1000
vector<vi> g; // graph
vi depth; // bfs depth per node
int n; // num of nodes

void bfs(int s) {
	queue<int> q; q.push(s);
	depth.assign(n,-1);
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