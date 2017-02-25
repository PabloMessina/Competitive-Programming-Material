// ==========================
// Find Tree's Diameter Ends
// ==========================
int dist[MAXN];
vector<vi> g;

int farthest_from(int s) {
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

void find_diameter(int& e1, int& e2) {
  e1 = farthest_from(0);
  e2 = farthest_from(e1);
}
