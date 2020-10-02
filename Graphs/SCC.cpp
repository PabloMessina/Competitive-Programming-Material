#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<b; ++i)
using namespace std;
// Tarjan's SCC algorithm
vector<int> s, D, L;
vector<bool> instack;
vector<vector<int>> g;
int n, ID;
void dfs(int u) {
    D[u] = L[u] = ID++;
    instack[u] = true;
    s.push_back(u);
    for (int v : g[u]) {
        if (D[v] == -1) {
            dfs(v);
            L[u] = min(L[v], L[u]);
        } else if (instack[v]) {
            L[u] = min(L[v], L[u]);
        }
    }
    if (L[u] == D[u]) { // u is root of a SCC
        cout << "SCC found!\n";        
        while (1) { // remove SCC from top of the stack
            int x = s.back(); s.pop_back();
            instack[x] = false;
            if (x == u) break;
        }
    }
}    
void find_sccs(vector<vector<int>>& g) {
    s.reserve(n); D.assign(n, -1); L.resize(n);
    instack.assign(n, 0);
    n = g.size(); ID = 0;
    rep(u,0,n) if (ids[u] == -1) dfs(u);
};
int main() {
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    while(m--) {
        int u, v; cin >> u >> v; u--, v--;
        g[u].push_back(v);
    }
    find_sccs(g);
    return 0;
}