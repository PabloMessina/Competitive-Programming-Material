// ==========================
// Find Tree's Diameter Ends
// ==========================
const int MAXN = 10000;

int farthest_from(vector<vi>& g, int s) {
    static int dist[MAXN];
    int farthest = s;
    int maxd = 0;
    memset(dist, -1, sizeof(dist[0]) * g.size());
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

void find_diameter(vector<vi>& g, int& e1, int& e2) {
    e1 = farthest_from(g, 0);
    e2 = farthest_from(g, e1);
}
