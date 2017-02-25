// =========================
// Depth First Search (DFS)
// =========================
#define MAXN 1000
vector<vi> g[MAXN];
bool visited[MAXN];
int n;

//iterative
void dfs(int root) {
	stack<int> s;
	s.push(root);
  visited[root] = true;
	while (!s.empty()) {
		int u = s.top(); s.pop();
		for (int v : g[u])
			if (!visited[v])
        visited[u] = true, s.push(v);
	}
}

//recursive
void dfs(int u) {
	visited[u] = true;
	for(int v : g[u])
		if(!visited[v]) 
			dfs(v);
}

//-----------------------------
// Finding connected components
//-----------------------------
int count_cc() {
  int count = 0;
  memset(visited,0,sizeof(bool)*n);
  rep(i,0,n-1)
    if (!visited[i])
      count++, dfs(i);
  return count;
}

//------------------------------
// Flood Fill
//------------------------------

//explicit graph
#define DFS_WHITE (-1)
vector<int> dfs_num(DFS_WHITE,n);
void floodfill(int u, int color) {
  dfs_num[u] = color;
  for (int v : g[u])
    if (dfs_num[v] == DFS_WHITE)
      floodfill(v, color);
}

//implicit graph
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
const char EMPTY = '*';
int floodfill(int r, int c, char color) {
	if (r < 0 || r >= R || c < 0 || c >= C) return 0; // outside grid
	if (grid[r][c] != EMPTY) return 0; // cannot be colored
  grid[r][c] = color;
	int ans = 1;
	rep(i,0,3) ans += floodfill(r + dirs[i][0], c + dirs[i][1], color);
	return ans;
}