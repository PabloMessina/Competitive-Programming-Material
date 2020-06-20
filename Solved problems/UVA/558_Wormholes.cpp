// tags: graphs, shortest path, bellman ford
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<vector<ii>> g(n);
        while (m--) {
            int u,v,w; cin >> u >> v >> w;
            g[u].emplace_back(v, w);
        }
        vector<int> d(n, INT_MAX);
        d[0] = 0;
        rep(_,1,n) {
            rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
                d[e.ff] = min(d[e.ff], d[u] + e.ss);
            }
        }
        bool neg = false;
        rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
            if (d[e.ff] > d[u] + e.ss) {
                neg = true; goto output;
            }
        }
        output:
        cout << (neg ? "possible\n" : "not possible\n");
    }
    return 0;
}