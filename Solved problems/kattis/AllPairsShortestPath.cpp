// tags: graphs, shortest paths, floyd warshall
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
    int n, m, q;
    while (cin >> n >> m >> q and n) {
        vector<vector<int>> g(n, vector<int>(n, INT_MAX));
        while (m--) {
            int u, v, w; cin >> u >> v >> w;
            g[u][v] = min(g[u][v], w);
        }
        rep(i,0,n) g[i][i] = min(g[i][i], 0);
        rep(k,0,n) rep(i,0,n) rep(j,0,n) {
            if (g[i][k] < INT_MAX and g[k][j] < INT_MAX) {
                g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
            }
        }
        while (q--) {
            int u, v; cin >> u >> v;
            if (g[u][v] == INT_MAX) {
                cout << "Impossible\n";
            } else {
                bool neg = false;
                rep(k,0,n) if (g[k][k] < 0 and g[u][k] < INT_MAX and g[k][v] < INT_MAX) {
                    neg = true; break;
                }
                if (neg) cout << "-Infinity\n";
                else cout << g[u][v] << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}