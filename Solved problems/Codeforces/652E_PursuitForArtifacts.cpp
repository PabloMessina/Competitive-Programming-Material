// tags: adhoc, DFS, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int N, M;
vector<vector<pair<int,bool>>> g;
vector<int> parent;
vector<bool> tag;
void dfs(int u, int p, bool a) {
    parent[u] = p;
    tag[u] = a;
    for (auto& x : g[u]) {
        int v = x.first;
        if (v == p) continue;
        if (tag[v]) continue;
        if (parent[v] == -1) {
            dfs(v, u, a or x.second);
        } else if (a or x.second) {
            dfs(v, parent[v], a or x.second);
        }
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    g.resize(N);
    while (M--) {
        int x, y, z;
        cin >> x >> y >> z;
        --x, --y;
        g[x].emplace_back(y, z);
        g[y].emplace_back(x, z);
    }
    int a, b; cin >> a >> b; --a, --b;
    tag.assign(N, false);
    parent.assign(N, -1);
    dfs(a, -1, false);
    cout << (tag[b] ? "YES" : "NO") << '\n';
    return 0;
}