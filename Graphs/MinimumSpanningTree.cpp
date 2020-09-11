#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=a; i<b; ++i)
#define ff first
#define ss second
typedef pair<int,int> ii;
/* ================= */
/* METHOD 1: KRUSKAL */
/* ================= */
struct Edge {
    int u, v, cost;
    bool operator<(const Edge& o) const { return cost < o.cost; }
};
namespace Kruskal {
    struct UnionFind {
        vector<int> p, rank;
        UnionFind(int n) {
            rank.assign(n,0);
            p.resize(n);
            rep(i,0,n) p[i] = i;
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
    int find_mst(int n_nodes, vector<Edge>& edges, vector<vector<ii>>& mst) {
        sort(edges.begin(), edges.end());
        UnionFind uf(n_nodes);
        mst.assign(n_nodes, vector<ii>());
        int mstcost = 0;
        int count = 1;
        for (auto& e : edges) {
            int u = e.u, v = e.v, cost = e.cost;
            if (!uf.isSameSet(u, v)) {
                mstcost += cost;
                uf.unionSet(u, v);
                mst[u].emplace_back(v, cost);
                mst[v].emplace_back(u, cost);
                if (++count == n_nodes) break;
            }
        }
        return mstcost;
    }
}
/* ============== */
/* METHOD 2: PRIM */
/* ============== */
struct Edge {
    int u, v, cost;
    bool operator<(const Edge& o) const { return cost > o.cost; } // notice > instead of <
};
namespace Prim {
    bool visited[MAXN];
    int find_mst(vector<vector<ii>>& g, vector<vector<ii>>& mst) {
        int n_nodes = g.size();
        memset(visited, false, sizeof(bool) * n_nodes);
        mst.assign(n_nodes, vector<ii>());
        priority_queue<Edge> q;
        int total_cost = 0;
        visited[0] = true;
        for (ii& p : g[0]) q.push({0, p.ff, p.ss});
        int count = 1;
        while (!q.empty()) {
            Edge e = q.top(); q.pop();
            int u = e.u, v = e.v, cost = e.cost;
            if (visited[v]) continue;
            visited[v] = true;
            total_cost += cost;
            mst[u].emplace_back(v, cost);
            mst[v].emplace_back(u, cost);
            if (++count == N) break;
            for (ii& p : g[v]) {
                if (visited[p.ff]) continue;
                q.push({v, p.ff, p.ss});                
            }            
        }
        return total_cost;
    }
}