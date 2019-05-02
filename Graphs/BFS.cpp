const int MAXN = 1000;
vector<int> g[MAXN]; // graph
int depth[MAXN]; // bfs depth per node
int n; // number of nodes

void bfs(int s) {
	memset(depth, -1, sizeof(int) * n); // init depth with -1
	queue<int> q; q.push(s); // init queue and add 's' (starting node)
	depth[s] = 0; // s will have depth 0
	while (!q.empty()) { // while there are nodes in the queue
		int u = q.front(); q.pop(); // extract the first node 'u' from the queue
		for (int v : g[u]) { // for each neighbor 'v' of 'u'
			if (depth[v] == -1) { // if 'v' has not been visited yet -> visit it
				depth[v] = depth[u] + 1;
				q.push(v);
			}
		}
	}
}