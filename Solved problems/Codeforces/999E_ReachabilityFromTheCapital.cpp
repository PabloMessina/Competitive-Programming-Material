// tags: dfs, directed graph, DAG, biconnected components
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
// -------------------------------
const int MAXN = 5005;
int N,M,S;
vector<vector<int>> g;
int ids[MAXN] = {0};
void dfs(int u, int id) {
    if (ids[u] == id) return;
    ids[u] = id;
    for (int v : g[u]) dfs(v, id);
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> S;
    g.resize(N+1);
    while (M--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
    }
    int ID = 1;
    rep(u,1,N) if (ids[u] == 0 and u != S) dfs(u, ID++);
    dfs(S, ID);
    uset<int> unique;
    rep(u,1,N) unique.insert(ids[u]);
    cout << unique.size() - 1 << '\n';
    return 0;
}