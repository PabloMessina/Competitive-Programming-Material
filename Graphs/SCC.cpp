// SCC = strongly connected components
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
using namespace std;

// ----------------------------------
// method 1: Tarjan's SCC algorithm
const int MAXN = 100000;

namespace tarjanSCC {
    const int UNVISITED = -1;
    vector<int> _stack;
    int ids[MAXN]; // ids[u] = id assigned to node u
    int low[MAXN]; // low[u] = lowest id reachable by node u
    bool instack[MAXN]; // instack[u] = if u is currently in stack or not
    int ID = 0; // global variable used to assign ids to unvisited nodes
    vector<vector<int>>* g; // pointer to graph

    void dfs(int u) {
        ids[u] = low[u] = ID++; // assign ID to new visited node
        // add to stack
        instack[u] = true;
        _stack.push_back(u);
        // check neighbor nodes
        for (int v : (*g)[u]) {
            if (ids[v] == UNVISITED) { // if unvisited -> visit 
                dfs(v);
                low[u] = min(low[v], low[u]); // update u's low
            } else if (instack[v]) { // visited AND in stack
                low[u] = min(low[v], low[u]); // update u's low
            }
        }
        if (low[u] == ids[u]) { // u is the root of a SCC
            // ** here you can do whatever you want
            // with the SCC just found
            cout << "SCC found!\n";
            // remove SCC from top of the stack
            while (true)  {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                if (x == u) break;
            }
        }
    }

    void run(vector<vector<int>>& _g) {
        _stack.reserve(MAXN); // reserve enough space to avoid memory reallocations
        int n = _g.size(); // number of nodes
        g = &_g; // pointer to graph
        // reset variables
        memset(ids, -1, sizeof(int) * n);
        memset(instack, 0, sizeof(bool) * n);
        ID = 0;
        // run dfs's
        rep(u, 0, n-1) if (ids[u] == UNVISITED) dfs(u);
    }
}

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
    tarjanSCC::run(g);
    return 0;
}