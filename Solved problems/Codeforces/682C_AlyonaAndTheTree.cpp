// tags: graphs, trees, DFS
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
int n;
int dfs(int u, int p, ll x) {
    if (a[u] < x) return 0;
    int ans = 1;
    for (auto& e : g[u]) if (e.ff != p) ans += dfs(e.ff, u, max(e.ss, e.ss + x));
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    g.resize(n);
    a.resize(n);
    rep(i,0,n) cin >> a[i];
    rep(i,1,n) {
        int p; ll c;
        cin >> p >> c; --p;
        g[i].emplace_back(p, c);
        g[p].emplace_back(i, c);
    }
    cout << n - dfs(0, -1, 0) << '\n';
    return 0;
}