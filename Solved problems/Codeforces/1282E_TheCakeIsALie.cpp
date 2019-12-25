// tags: implementation, graphs, adhoc
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
int n;
struct Triangle {
    int a, b, c, id;
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n;
        vector<Triangle> triangles(n-2);
        int id = 0;
        map<pair<int,int>, vector<int>> edge2tri;
        auto add_edge = [&edge2tri](int a, int b, int id) {
            if (a > b) swap(a,b);
            edge2tri[{a,b}].push_back(id);
        };
        for (auto& tr : triangles) {
            cin >> tr.a >> tr.b >> tr.c;
            tr.a--, tr.b--, tr.c--;
            tr.id = id++;
            add_edge(tr.a, tr.b, tr.id);
            add_edge(tr.b, tr.c, tr.id);
            add_edge(tr.c, tr.a, tr.id);
        }
        assert (id == n-2);
        vector<vector<int>> g_per(n);
        vector<vector<int>> g_tri(n-2);
        for (auto& p : edge2tri) {
            auto& e = p.first;
            auto& ids = p.second;
            if (ids.size() == 1) {
                g_per[e.first].push_back(e.second);
                g_per[e.second].push_back(e.first);
            } else if (ids.size() == 2) {
                g_tri[ids[0]].push_back(ids[1]);
                g_tri[ids[1]].push_back(ids[0]);
            } else {
                assert (false);
            }
        }
        // perimeter
        {
            vector<bool> vis(n, 0);
            int u = 0;
            bool f = true;
            while (1) {
                vis[u] = true;
                if (f) f = false;
                else cout << ' ';
                cout << u+1;
                int nxt_u = -1;
                for (int v : g_per[u]) {
                    if (vis[v]) continue;
                    nxt_u = v; break;
                }
                if (nxt_u == -1) break;
                u = nxt_u;
            }
            cout << '\n';
        }
        // triangles
        {
            if (n-2 == 1) {
                cout << "1\n";
                continue;
            }
            vector<int> indegree(n-2);
            vector<bool> vis(n-2, 0);
            queue<int> q;
            rep(u,0,n-2) {
                indegree[u] = g_tri[u].size();
                if (indegree[u] == 1) {
                    q.push(u); vis[u] = true;
                }
            }
            bool f = true;
            while (!q.empty()) {
                int u = q.front(); q.pop();
                if (f) f = false;
                else cout << ' ';
                cout << u+1;
                for (int v : g_tri[u]) {
                    if (--indegree[v] <= 1 and not vis[v]) {
                        q.push(v); vis[v] = true;
                    }
                }
            }
            cout << '\n';
        }
    }
    return 0;
}