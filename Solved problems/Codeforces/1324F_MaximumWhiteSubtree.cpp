#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
const int MAXN = 200000;
int color[MAXN];
vector<int> g[MAXN];
int n;

pair<int,int> idx2edge[2 * MAXN];
umap<ll, int> edge2idx;
int get_edge_idx(ll u, ll v) {
    ll e = u * n + v;
    auto it = edge2idx.find(e);
    if (it == edge2idx.end()) {
        int idx = edge2idx.size();
        edge2idx[e] = idx;
        idx2edge[idx] = {u, v};
        return idx;
    }
    return it->second;
}

int memo[2 * MAXN];
int dp(int e) {
    int& ans = memo[e];
    if (ans != -1) return ans;
    int p, u; tie(p, u) = idx2edge[e];
    // assert (0 <= p and p < n);
    // assert (0 <= u and u < n);
    ans = color[u] ? 1 : -1;
    for (int v : g[u]) {
        if (v == p) continue;
        int uv = get_edge_idx(u, v);
        ans += dp(uv);
    }
    if (ans < 0) ans = 0;
    return ans;
}

int max_score(int u) {
    int ans = 0;
    for (int v : g[u]) {
        int e = get_edge_idx(u, v);
        ans += dp(e);                
    }
    ans += color[u] ? 1 : -1;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> n;
    rep(i,0,n) cin >> color[i];
    rep(i,0,n-1) {
        int u, v; cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    memset(memo, -1, sizeof(int) * 2 * n);
    rep(u,0,n) {
        if (u) cout << ' ';
        cout << max_score(u);
    }
    cout << '\n';
    return 0;
}