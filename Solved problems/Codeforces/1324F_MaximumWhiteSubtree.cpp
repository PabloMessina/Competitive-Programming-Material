// tags: DP, DFS, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXN = 200000;
int color[MAXN];
vector<int> g[MAXN];

int memo1[MAXN];
int dfs1(int u, int p) {
    int ans = color[u] ? 1 : -1;
    for (int v : g[u]) {
        if (v == p) continue;
        ans += max(dfs1(v, u), 0);
    }
    return memo1[u] = ans;
}

int memo2[MAXN];
void dfs2(int u, int p) {
    memo2[u] = memo1[u];
    if (p != -1) memo2[u] += max(memo2[p] - max(0, memo1[u]), 0);
    for (int v : g[u]) {
        if (v == p) continue;
        dfs2(v, u);
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    rep(i,0,n) cin >> color[i];
    rep(_,1,n) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs1(0, -1);
    dfs2(0, -1);
    rep(i,0,n) {
        if (i) cout << ' ';
        cout << memo2[i];
    }
    cout << '\n';
    return 0;
}