#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
using namespace std;
// -----------------------------------------
// implementation of Tarjan's SCC algorithm
struct tarjanSCC {
    vector<int> _stack, ids, low;
    vector<bool> instack;
    vector<vector<int>>* g;
    int n, ID;
    void dfs(int u) {
        ids[u] = low[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (int v : (*g)[u]) {
            if (ids[v] == -1) {
                dfs(v);
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[v], low[u]);
            }
        }
        if (low[u] == ids[u]) {
            // u is the root of a SCC
            // ** here you can do whatever you want
            // with the SCC just found
            cout << "SCC found!\n";
            // remove SCC from top of the stack
            while (1) {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                if (x == u) break;
            }
        }
    }
    tarjanSCC(vector<vector<int>>& _g) {
        g = &_g;
        n = _g.size();
        _stack.reserve(n);
        ids.assign(n, -1);
        low.resize(n);
        instack.assign(n, 0);
        ID = 0;
        rep(u, 0, n-1) if (ids[u] == -1) dfs(u);
    }
};

// example of usage
int main() {
    // read and build graph from standard input
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    while(m--) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
    }
    // find SCCs
    tarjanSCC tscc(g);
    return 0;
}