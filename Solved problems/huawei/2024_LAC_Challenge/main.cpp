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
int M;
const int MAXM = 50000;
vector<vi> g;

void dfs(int u, int p, vi& edge_to, vi& visited, vi& depth, vector<vi>& cycles) {
    visited[u] = 0;
    for (int v : g[u]) {
        if (v == p) continue;
        if (visited[v] == -1) {
            edge_to[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, u, edge_to, visited, depth, cycles);
        } else if (visited[v] == 0) {
            vi cycle;
            int x = u;
            while (x != v) {
                cycle.pb(x);
                x = edge_to[x];
            }
            cycle.pb(v);
            cycles.pb(cycle);
        }
    }
    visited[u] = 1;
}

// vector<vi> find_cycle_basis_suboptimal() {
//     int n = g.size();
//     vector<vi> cycles;
//     vi edge_to(n, -1), visited(n, -1), depth(n, -1);
//     rep(u,0,n) if (visited[u] == -1) dfs(u, -1, edge_to, visited, depth, cycles);
//     return cycles;
// }

ll hash_edge(int u, int v, int num_nodes) {
    if (u > v) swap(u, v);
    return (ll)u * num_nodes + v;
}

vector<vi> spanning_tree(uset<ll>& edge_set) {
    int n = g.size();
    vi edge_to(n, -1), visited(n, -1), depth(n, -1);
    vector<vi> cycles;
    rep(u,0,n) if (visited[u] == -1) dfs(u, -1, edge_to, visited, depth, cycles);
    vector<vi> tree(n);
    rep(u,0,n) if (edge_to[u] != -1) {
        tree[u].pb(edge_to[u]);
        tree[edge_to[u]].pb(u);
        edge_set.insert(hash_edge(u, edge_to[u], n));
    }
    return tree;
}

struct LCA {
    vector<int> A, D; // ancestors, depths
    vector<vector<int>> *g; // pointer to graph
    int n, maxe; // num nodes, max exponent
    int& anc(int u, int e) { return A[e * n + u]; }    
    int inline log2(int x) { return 31 - __builtin_clz(x); }
    // dfs to record direct parents and depths
    void dfs(int u, int p, int depth) {
        anc(u,0) = p;
        D[u] = depth;
        for (int v : (*g)[u]) if (D[v] == -1) dfs(v, u, depth + 1);
    }
    LCA(vector<vector<int>>& _g, int root) {
        g = &_g;
        n = _g.size();
        maxe = log2(n);
        D.assign(n, -1);
        A.resize(n * (maxe + 1));
        dfs(root, -1, 0);
        rep(e,1,maxe+1) {
            rep(u,0,n) {
                // u's 2^e th ancestor is
                // u's 2^(e-1) th ancestor's 2^(e-1) th ancestor
                int a = anc(u,e-1);
                anc(u,e) = (a == -1 ? -1 : anc(a,e-1));
            }
        }
    }
    // move node u "k" levels up towards the root
    // i.e. find the k-th ancestor of u
    int raise(int u, int k) {
        for (int e = 0; k; e++, k>>=1) if (k&1) u = anc(u,e);
        return u;
    }
    int lca(int u, int v) {
        if (D[u] < D[v]) swap(u, v); 
        u = raise(u, D[u] - D[v]); // raise lowest to same level
        if (u == v) return u; // same node, we are done
        // raise u and v to their highest ancestors below the LCA
        invrep(e,maxe,0) {
            // greedily take the biggest 2^e jump possible as long as 
            // u and v still remain BELOW the LCA
            if (anc(u,e) != anc(v,e)) u = anc(u,e), v = anc(v,e);
        }
        // the direct parent of u (or v) is lca(u,v)
        return anc(u,0);
    }
    vector<int> path(int u, int v) {
        vector<int> from_u_to_lca;
        vector<int> from_v_to_lca;
        int lca_uv = lca(u,v);
        while (u != lca_uv) {
            from_u_to_lca.pb(u);
            u = anc(u,0);
        }
        while (v != lca_uv) {
            from_v_to_lca.pb(v);
            v = anc(v,0);
        }
        vector<int> path;
        for (int x : from_u_to_lca) path.pb(x);
        path.pb(lca_uv);
        for (int i = from_v_to_lca.size() - 1; i >= 0; --i) path.pb(from_v_to_lca[i]);
        return path;
    }
};

int main() {
    ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> M; // number of edges
    vector<ii> edges;
    g.reserve(MAXM);
    rep(_,0,M) { // read edges
        int u, v;
        std::cin >> u >> v;
        --u, --v; // 0-based indexing
        edges.eb(u,v);
        if (g.size() <= max(u,v)) g.resize(max(u,v)+1);
        g[u].pb(v);
        g[v].pb(u);
    }
    // find spanning tree
    uset<ll> edge_set;
    vector<vi> tree = spanning_tree(edge_set);
    // std::cout << "Spanning tree edges:\n";
    // for (int u = 0; u < tree.size(); ++u) {
    //     for (int v : tree[u]) {
    //         cout << u+1 << ' ' << v+1 << '\n';
    //     }
    // }
    // std::cout << "edge_set.size() = " << edge_set.size() << '\n';
    // build LCA from the tree
    LCA lca(tree, 0);
    // for each (u, v) not in the tree, find the path from u to v
    vector<vi> paths;
    for (ii& e : edges) {
        int u = e.ff, v = e.ss;
        if (edge_set.count(hash_edge(u,v,g.size()))) continue;
        // std::cout << "Path from " << u+1 << " to " << v+1 << ":\n";
        vector<int> p = lca.path(u, v);
        paths.pb(p);
    }
    // print cycles (by closing the paths)
    std::cout << paths.size() << '\n';
    for (vi& path : paths) {
        std::cout << path.size()+1 << ' ';
        for (int u : path) std::cout << u+1 << ' ';
        std::cout << path[0]+1; // cycle is a cycle, so it ends where it starts
        std::cout << '\n';
    }
}