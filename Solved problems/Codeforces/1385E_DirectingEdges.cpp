// tags: graphs, DAG, dfs
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
vector<vector<int>> g, gg;

int RANK = 0;
vector<int> ranks;
bool isDAG(vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indegree(n,0);
    rep(u,0,n) for (int v : g[u]) indegree[v]++;
    queue<int> q;
    int count = 0;
    rep(u,0,n) if (indegree[u] == 0) {
        q.push(u);
        ranks[u] = RANK++;
    }
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : g[u]) if (--indegree[v] == 0) {
            q.push(v);
            ranks[v] = RANK++;
        }
    }
    return count == n;
}

int ID = 0;
vector<int> ids;
void dfs(int u) {
    ids[u] = ID;
    for (int v : gg[u]) if (ids[v] == -1) dfs(v);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        vector<pair<int,int>> uedges, dedges;
        g.assign(n, vector<int>());
        gg.assign(n, vector<int>());
        rep(_,0,m) {
            int c, x, y; cin >> c >> x >> y; --x, --y;
            if (c) {
                g[x].push_back(y);
                dedges.emplace_back(x, y);
            } else {
                gg[x].push_back(y);
                gg[y].push_back(x);
                uedges.emplace_back(x, y);
            }
        }
        ranks.resize(n);        
        if (!isDAG(g)) cout << "NO\n";
        else {
            cout << "YES\n";            
            ids.assign(n, -1);
            rep(u,0,n) {
                if (ids[u] == -1) dfs(u);
            }
            for (auto& e : dedges) {
                cout << (e.ff+1) << ' ' << (e.ss+1) << '\n';
            }
            for (auto& e : uedges) {
                if (tie(ids[e.ff], ranks[e.ff]) < tie(ids[e.ss], ranks[e.ss])) {
                    cout << (e.ff+1) << ' ' << (e.ss+1) << '\n';
                } else {
                    cout << (e.ss+1) << ' ' << (e.ff+1) << '\n';
                }
            }
        }
    }
    return 0;
}