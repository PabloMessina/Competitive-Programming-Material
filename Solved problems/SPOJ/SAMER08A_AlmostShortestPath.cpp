// tags: graphs, dijkstra
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
vector<int> dijkstra(int s, vector<vector<ii>>& g) {
    int n = g.size();
    priority_queue<ii, vector<ii>, greater<ii>> q;
    vector<int> dist(n, INT_MAX);
    q.emplace(0, s);
    dist[s] = 0;
    while (q.size()) {
        int d, u; tie(d, u) = q.top(); q.pop();
        if (dist[u] < d) continue;
        for (auto& e : g[u]) {
            if (d + e.ss < dist[e.ff]) {
                dist[e.ff] = d + e.ss;
                q.emplace(dist[e.ff], e.ff);
            }
        }
    }
    return dist;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M;
    while (cin >> N >> M and N) {        
        vector<vector<ii>> g(N), gr(N), g2(N);
        int s, d; cin >> s >> d;
        rep(_,0,M) {
            int u, v, p; cin >> u >> v >> p;
            g[u].emplace_back(v, p);
            gr[v].emplace_back(u, p);
        }
        vector<int> dist = dijkstra(s, g);
        if (dist[d] == INT_MAX) {
            cout << "-1\n";
            continue;
        }
        vector<int> dist_r = dijkstra(d, gr);
        rep(u,0,N) for (auto& p : g[u]) {
            if (dist[u] < INT_MAX and dist_r[p.ff] < INT_MAX and
                dist[u] + p.ss + dist_r[p.ff] == dist[d]) continue;
            g2[u].emplace_back(p.ff, p.ss);
        }
        vector<int> dist2 = dijkstra(s, g2);
        cout << (dist2[d] == INT_MAX ? -1 : dist2[d]) << '\n';
    }
    return 0;
}