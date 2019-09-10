// tags: MST, DFS, graphs, bitwise, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
typedef pair<int,int> ii;
// -------------------------------
struct Edge {
    int u, v, cost;
    bool operator<(const Edge& o) const {
        return cost < o.cost;
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

int N, M;
vector<vector<ii>> mst;
const int MAXL = 1000000;
int bits[MAXL];

void add_bits(ll val, int offset) {
    int i, r = 0;
    for (i = offset; val > 0 or r > 0; val >>=1, i++) {
        bits[i] += (val & 1) + r;
        r = bits[i] >> 1;
        bits[i] &= 1;
    }
}

ll dfs(int u, int p, int p_cost) {
    ll size = 1;
    for (auto& e : mst[u]) {
        if (e.first == p) continue;
        int v, cost; tie(v,cost) = e;
        size += dfs(v, u, cost);
    }
    if (p != -1) add_bits((N-size) * size, p_cost);
    return size;
}

void print_bits() {
    int i = MAXL-1;
    while (i >= 0 and bits[i] == 0) --i;
    if (i < 0) cout << "0\n";    
    else {
        invrep(j, i, 0) cout << bits[j];
        cout << '\n';
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    vector<Edge> edges;
    edges.reserve(M);
    while (M--) {
        int u, v, c; cin >> u >> v >> c;
        --u, --v;
        edges.push_back({u,v,c});
    }    
    Kruskal::find_mst(N, edges, mst);
    dfs(0, -1, 0);
    print_bits();
    return 0;
}