// tags: SCC, tarjan, dfs, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
struct tarjanSCC {
    vector<int> _stack, ids, low;
    vector<bool> instack, vis;
    vector<vector<int>> *g, *rg;
    int n, ID;
    int dfs_rg(int u) {
        vis[u] = true;
        int count = 1;
        for (int v : (*rg)[u]) if (!vis[v]) count += dfs_rg(v);
        return count;
    }
    bool dfs(int u) {
        ids[u] = low[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (int v : (*g)[u]) {
            if (ids[v] == -1) {
                if (dfs(v)) return true;
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[v], low[u]);
            }
        }
        if (low[u] == ids[u]) {
            vis.assign(n, 0);
            if (dfs_rg(u) == n) {
                int i = _stack.size() - 1;
                while (_stack[i] != u) --i;
                sort(_stack.begin() + i, _stack.end());
                cout << (_stack.size() - i) << '\n';
                rep(j,i,_stack.size()-1) {
                    if (j > i) cout << ' ';
                    cout << _stack[j]+1;
                }
                cout << '\n';
            } else {
                cout << "0\n\n";
            }
            return true;
        }
        return false;
    }
    tarjanSCC(vector<vector<int>>& _g, vector<vector<int>>& _rg) {
        g = &_g;
        rg = &_rg;
        n = _g.size();
        _stack.reserve(n);
        ids.assign(n, -1);
        low.resize(n);
        instack.assign(n, 0);
        ID = 0; dfs(0);
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    vector<vector<int>> g(N), rg(N);
    while (M--) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }    
    tarjanSCC tscc(g, rg);
    return 0;
}