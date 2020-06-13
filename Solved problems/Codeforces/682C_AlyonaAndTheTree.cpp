// tags: graphs, trees, DFS, DP
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define ff first
#define ss second
typedef long long int ll;
// -------------------------------
vector<vector<pair<int,ll>>> g;
vector<ll> a;
vector<bool> erase;
int n;
void dfs(int u, int p, ll x) {
    if (a[u] < x) erase[u] = true;
    for (auto& e : g[u]) if (e.ff != p) dfs(e.ff, u, max(e.ss, e.ss + x));
}
int dfs2(int u, int p) {
    if (erase[u]) return 0;
    int ans = 1;
    for (auto& e : g[u]) if (e.ff != p) ans += dfs2(e.ff, u);
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    g.resize(n);
    a.resize(n);
    erase.assign(n, false);
    rep(i,0,n) cin >> a[i];
    rep(i,1,n) {
        int p; ll c;
        cin >> p >> c; --p;
        g[i].emplace_back(p, c);
        g[p].emplace_back(i, c);
    }
    dfs(0, -1, 0);
    cout << n - dfs2(0, -1) << '\n';
    return 0;
}