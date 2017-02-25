vi depth(N,-1);
vi low(N);
vector<vi> g(N, vi());
int rootChildren = 0;

void dfs(int u, int p, int d) { // (node, parent, depth)
  depth[u] = d;
  low[u] = d;
  for(int v : g[u]) {
    if (v == p) continue; // direct edge to parent is not back edge
    if (depth[v] == -1) {
      if (p == -1 && ++rootChildren > 1) // root
          printf("root = %d is articulation point\n", root);

      dfs(v, u, d + 1);

      if (low[v] >= depth[u] && p != -1)
        printf("u = %d is articulation point\n",  u);

      if (low[v] > depth[u])
        printf("(u,v) = (%d, %d) is cut edge\n", u, v);

      if (low[v] < low[u]) low[u] = low[v];

    } else if (depth[v] < low[u]) {
      low[u] = depth[v];
    }
  }
}