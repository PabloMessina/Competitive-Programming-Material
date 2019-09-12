// tags: Kruskal, MST, union find, DFS, cut edges, tarjan, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
typedef pair<int,int> ii;
// -------------------------------
enum { SOME, NONE, ALL };
struct Edge {
    int u, v, w, i, type;
    Edge(int u, int v, int w, int i, int type) :
         u(u), v(v), w(w), i(i), type(type) {}
    Edge() {}
    bool operator<(const Edge& o) const {
        return w < o.w;
    }
};

namespace Kruskal {
    struct UnionFind {
        vector<int> p, rank;
        UnionFind(int n) {
            rank.assign(n,0);
            p.resize(n);
            rep(i,0,n-1) p[i] = i;
        }
        int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
        bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
        void unionSet(int i, int j) {
            if (!isSameSet(i, j)) {
                int x = findSet(i), y = findSet(j);
                if (rank[x] > rank[y]) { p[y] = x; }
                else { p[x] = y; if (rank[x] == rank[y]) rank[y]++; }
            }
        }
    };

    vector<vector<pair<int, Edge*>>> g;
    map<ii, int> edge_count;
    vector<int> depth, low;

    void dfs(int u, int p, int d) {
        depth[u] = d;
        low[u] = d;
        for(auto& e : g[u]) {
            int v = e.first;
            if (v == p) continue;
            if (depth[v] == -1) {
                dfs(v, u, d + 1);
                if (low[v] > depth[u] and edge_count[{u,v}] == 1) {
                    e.second->type = ALL;
                }
                low[u] = min(low[u], low[v]); 
            } else if (depth[v] < low[u]) {
                low[u] = depth[v];
            }
        }
    }

    void run(int n_nodes, vector<Edge>& edges) {
        sort(edges.begin(), edges.end());
        UnionFind uf(n_nodes);
        int l = 0, r = 0;
        int m = edges.size();
        while (l < m) {
            while (r < m and edges[r].w == edges[l].w) ++r;
            
            umap<int, int> set2id;
            int ID  = 0;
            rep(i,l,r-1) {
                Edge& e = edges[i];
                
                int set_u = uf.findSet(e.u);                
                auto it_u = set2id.find(set_u);
                if (it_u == set2id.end()) set2id.emplace(set_u, ID++);
                
                int set_v = uf.findSet(e.v);
                auto it_v = set2id.find(set_v);
                if (it_v == set2id.end()) set2id.emplace(set_v, ID++);
            }

            g.assign(ID, vector<pair<int, Edge*>>());
            edge_count.clear();

            rep(i,l,r-1) {
                Edge& e = edges[i];
                int u = set2id[uf.findSet(e.u)];
                int v = set2id[uf.findSet(e.v)];
                if (u == v) {
                    e.type = NONE;
                } else {
                    g[u].emplace_back(v, &e);
                    g[v].emplace_back(u, &e);
                    edge_count[{u,v}]++;
                    edge_count[{v,u}]++;
                }
            }
            depth.assign(ID, -1);
            low.resize(ID);
            rep(u, 0, ID-1) if (depth[u] == -1) dfs(u, -1, 0);

            rep(i,l,r-1) {
                Edge& e = edges[i];
                uf.unionSet(e.u, e.v);
            }

            l = r;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int N, M; cin >> N >> M;
    vector<Edge> edges; edges.reserve(M);
    rep(i,0,M-1) {
        int u, v, w; cin >> u >> v >> w;
        --u, --v;
        edges.emplace_back(u,v,w,i,SOME);
    }
    Kruskal::run(N, edges);
    vector<int> indexes(M);
    rep(i,0,M-1) indexes[edges[i].i] = i;
    for (int i : indexes) {
        Edge& e = edges[i];
        if (e.type == SOME) {
            cout << "at least one\n";
        } else if (e.type == ALL) {
            cout << "any\n";
        } else {
            assert (e.type == NONE);
            cout << "none\n";
        }
    }
    return 0;
}