#include "../c++_template.cpp"
// complexity: O(|V||E|)
vector<int> bellman_ford(vector<vector<ii>>& g, int s, bool& neg_cycle) {
    int n = g.size();
    vector<int> d(n, INT_MAX); // store min distance from s to all nodes
    d[s] = 0;
    rep(_,1,n)  rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
        d[e.ff] = min(d[e.ff], d[u] + e.ss);
    }
    // optional: detect negative cycle
    rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
        if (d[e.ff] > d[u] + e.ss) {
            neg_cycle = true; return d;
        }
    }
    return d;
}