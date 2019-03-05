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
    int ids[MAXN];
    int lows[MAXN];
    bool instack[MAXN];
    int ID = 0;
    vector<vector<int>>* g;
    int N;

    void dfs(int u) {
        ids[u] = lows[u] = ID++; // assign ID to new visited node
        // add to stack
        instack[u] = true;
        _stack.push_back(u);
        // check neighbor nodes
        for (int v : (*g)[u]) {
            if (ids[v] == UNVISITED) { // if unvisited -> visit 
                dfs(v);
                lows[u] = min(lows[v], lows[u]); // update u's low
            } else if (instack[v]) { // visited AND in stack
                lows[u] = min(lows[v], lows[u]); // update u's low
            }
        }
        if (lows[u] == ids[u]) { // u is the root of a SCC
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

    void tarjanSCC(vector<vector<int>>& _g) {
        _stack.reserve(MAXN); // reserve enough space to avoid memory reallocations
        N = _g.size(); // number of nodes
        g = &_g; // pointer to graph
        // reset variables
        memset(ids, -1, sizeof(int) * N);
        memset(instack, 0, sizeof(bool) * N);
        ID = 0;
        // run dfs's
        rep(u, 0, N-1) if (ids[u] == UNVISITED) dfs(u);
    }
}

// example of usage
int main() {
    // read and build graph from standard input
    int N, m; cin >> N >> M;
    vector<vector<int>> g(N);
    rep(i,1,M) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }
    // find SCCs
    tarjanSCC(g);
    return 0;
}

// -----------------------------------
// method 2: Kosaraju's SCC algorithm
// TODO: finish this