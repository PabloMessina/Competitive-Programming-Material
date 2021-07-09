// complexity: O(|V|^3)
#define rep(i,a,b) for(int i=a; i<b; ++i)
void floyd_warshall(vector<vector<int>>& g, bool& neg_cycle) {
    int n = g.size();
    rep(k,0,n) rep(i,0,n) rep(j,0,n) {
        if (g[i][k] < INT_MAX and g[k][j] < INT_MAX) {
            g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
    }
    // optional: detect negative cycle
    rep(k,0,n) if (g[k][k] < 0) {
        rep(i,0,n) rep(j,0,n) if (g[i][k] < INT_MAX and g[k][j] < INT_MAX) {
            neg_cycle = true; return;
        }
    }
}