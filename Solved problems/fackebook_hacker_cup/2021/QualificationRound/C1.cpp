#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
vector<vi> g;
vector<ll> C;
ll dfs(int u, int p) {
    ll ans = 0;
    for (int v : g[u]) {
        if (v == p) continue;
        ans = max(ans, dfs(v, u));
    }
    return C[u] + ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(t, 1, T+1) {
        int N; cin >> N;
        g.assign(N, vi()), C.resize(N);
        rep(i,0,N) cin >> C[i];
        rep(i,1,N) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].push_back(v);
            g[v].push_back(u);                    
        }
        cout << "Case #" << t << ": ";
        if (g[0].size() <= 1) {
            cout << dfs(0, -1) << '\n';
        } else {
            ll b1 = 0, b2 = 0;
            for (int v : g[0]) {
                int x = dfs(v, 0);
                if (x > b1) { b2 = b1; b1 = x; }
                else if (x > b2) { b2 = x; }
            }
            cout << C[0] + b1 + b2 << '\n';
        }
    }
    return 0;
}