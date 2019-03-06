// tags: SCC, tarjan, BFS, graphs
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

const int MAXN = 2000;
int N;
vector<vector<int>> g;
vector<vector<int>> rg;

namespace tarjanSCC {
    const int UNVISITED = -1;
    vector<int> _stack;
    int ids[MAXN]; // ids[u] = id assigned to node u
    int lows[MAXN]; // lows[u] = lowest id reachable by node u
    bool instack[MAXN]; // instack[u] = if u is currently in stack or not
    int ID = 0; // global variable used to assign ids to unvisited nodes
    vector<vector<int>>* g; // pointer to graph
    vector<vector<int>>* rg; // pointer to reversed-edge graph

    // BFS to count reachable nodes from 'x' in reversed graph
    int count_reachable_in_rg(int x) {
        static bool visited[MAXN];
        memset(visited, 0, sizeof(bool) * rg->size());
        queue<int> q;
        q.push(x);
        visited[x] = true;
        int count = 1;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : (*rg)[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    q.push(v);
                    count++;
                }
            }
        }
        return count;
    }

    bool dfs(int u) {
        ids[u] = lows[u] = ID++; // assign ID to new visited node
        // add to stack
        instack[u] = true;
        _stack.push_back(u);
        // check neighbor nodes
        for (int v : (*g)[u]) {
            if (ids[v] == UNVISITED) { // if unvisited -> visit 
                if (dfs(v)) return true;
                lows[u] = min(lows[v], lows[u]); // update u's low
            } else if (instack[v]) { // visited AND in stack
                lows[u] = min(lows[v], lows[u]); // update u's low
            }
        }
        if (lows[u] == ids[u]) { // u is the root of a SCC
            // check if we can reach the whole graph from node u
            if (count_reachable_in_rg(u) == rg->size()) {
                // if so, all nodes in the scc are candidates
                vector<int> scc_nodes;
                while (true)  {
                    int x = _stack.back(); _stack.pop_back();
                    instack[x] = false;
                    scc_nodes.push_back(x);
                    if (x == u) break;
                }
                sort(scc_nodes.begin(), scc_nodes.end());
                for (int x : scc_nodes) cout << x+1 << " ";
            }
            cout << "0\n";
            return true;
        }
        return false;
    }

    void run(vector<vector<int>>& _g, vector<vector<int>>& _gr) {
        _stack.reserve(MAXN); // reserve enough space to avoid memory reallocations
        int n = _g.size(); // number of nodes
        g = &_g; // pointer to graph
        rg = &_gr; // pointer to reversed-edge graph
        // reset variables
        memset(ids, -1, sizeof(int) * n);
        memset(instack, 0, sizeof(bool) * n);
        ID = 0;
        // run dfs's
        rep(u, 0, n-1) if (ids[u] == UNVISITED && dfs(u)) break;
    }
}

int main() {
    // for faster input/output
    ios::sync_with_stdio(false);
    cin.tie(0);
    // --------
    cin >> N;
    g.resize(N);
    rg.resize(N);
    rep(i,0,N-1) {
        int j; while ((cin >> j) and j > 0) {
            g[i].push_back(j-1);
            rg[j-1].push_back(i);
        }
    }
    tarjanSCC::run(rg, g);
    return 0;
}