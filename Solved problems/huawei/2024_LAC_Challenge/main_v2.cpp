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
const double EPS = 1e-9;
const int INF = 2;

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

vector<vi> spanning_tree(uset<ll>& edge_set, vector<int>& node_order) {
    int n = g.size();
    vi edge_to(n, -1), visited(n, -1), depth(n, -1);
    vector<vi> cycles;
    // rep(u,0,n) if (visited[u] == -1) dfs(u, -1, edge_to, visited, depth, cycles);
    for (int u : node_order) if (visited[u] == -1) dfs(u, -1, edge_to, visited, depth, cycles);
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

int compute_rank(vector<vector<double>> A) {
    int n = A.size();
    int m = A[0].size();

    int rank = 0;
    vector<bool> row_selected(n, false);
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n; ++j) {
            if (!row_selected[j] && abs(A[j][i]) > EPS)
                break;
        }

        if (j != n) {
            ++rank;
            row_selected[j] = true;
            for (int p = i + 1; p < m; ++p)
                A[j][p] /= A[j][i];
            for (int k = 0; k < n; ++k) {
                if (k != j && abs(A[k][i]) > EPS) {
                    for (int p = i + 1; p < m; ++p)
                        A[k][p] -= A[j][p] * A[k][i];
                }
            }
        }
    }
    return rank;
}

// Function to check if cycles in a cycle basis are independent
bool are_cycles_independent(const umap<ll,int>& edge_hash_to_index, vector<vi>& cycle_basis) {
    // Create the matrix
    int num_edges = edge_hash_to_index.size();
    int num_nodes = g.size();
    int num_cycles = cycle_basis.size();
    vector<vector<double>> matrix(num_cycles, vector<double>(num_edges, 0));
    for (size_t i = 0; i < cycle_basis.size(); ++i) {
        for (size_t j = 0; j < cycle_basis[i].size(); ++j) {
            int u = cycle_basis[i][j];
            int v = cycle_basis[i][(j + 1) % cycle_basis[i].size()];
            matrix[i][edge_hash_to_index.at(hash_edge(u,v,num_nodes))] = 1;
        }
    }
    int rank = compute_rank(matrix);
    
    // // Print the matrix
    // for (size_t i = 0; i < matrix.size(); ++i) {
    //     for (size_t j = 0; j < matrix[i].size(); ++j) {
    //         cout << matrix[i][j] << ' ';
    //     }
    //     cout << '\n';
    // }
    // cout << "rank = " << rank << '\n';
    
    return rank == num_cycles;
}

void update_cycle_basis(vector<vi>& final_paths, int& min_cost,
    vector<ii>& edges, mt19937& rng, umap<ll,int>& edge_hash_to_index) {
    
    // choose a random noder order
    int n = g.size();
    vector<int> node_order(n);
    std::iota(node_order.begin(), node_order.end(), 0);
    // std::random_shuffle(node_order.begin(), node_order.end());
    std::shuffle(node_order.begin(), node_order.end(), rng);

    // cout << "node_order: ";
    // for (int u : node_order) cout << u+1 << ' ';
    // cout << '\n';

    // find spanning tree
    uset<ll> edge_set;
    vector<vi> tree = spanning_tree(edge_set, node_order);
    // std::cout << "Spanning tree edges:\n";
    // for (int u = 0; u < tree.size(); ++u) {
    //     for (int v : tree[u]) {
    //         cout << u+1 << ' ' << v+1 << '\n';
    //     }
    // }
    // std::cout << "edge_set.size() = " << edge_set.size() << '\n';
    
    // choose a random root
    int root = node_order[0];

    // cout << "root = " << root+1 << '\n';
    
    // build LCA from the tree
    LCA lca(tree, root);
    
    // for each (u, v) not in the tree, find the path from u to v
    vector<vi> paths;
    for (ii& e : edges) {
        int u = e.ff, v = e.ss;
        if (edge_set.count(hash_edge(u,v,g.size()))) continue;
        vector<int> p = lca.path(u, v);
        paths.pb(p);
    }

    // compute the cost of these paths
    int cost = 0;
    for (vi& path : paths) cost += path.size();

    // std::cout << "cost found: " << cost << '\n';

    // if the cost is less than the current minimum, update the minimum
    if (cost < min_cost) {
        if (are_cycles_independent(edge_hash_to_index, paths)) {
            min_cost = cost;
            final_paths = paths;
        }
    }
}

int main() {
    ios::sync_with_stdio(false); std::cin.tie(0);

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    std::cin >> M; // number of edges
    vector<ii> edges;
    g.reserve(MAXM);
    rep(i,0,M) { // read edges
        int u, v;
        std::cin >> u >> v;
        --u, --v; // 0-based indexing
        edges.eb(u,v);
        if (g.size() <= max(u,v)) g.resize(max(u,v)+1);
        g[u].pb(v);
        g[v].pb(u);
    }

    umap<ll,int> edge_hash_to_index;
    for (size_t i = 0; i < edges.size(); ++i) {
        edge_hash_to_index[hash_edge(edges[i].ff, edges[i].ss, g.size())] = i;
    }

    // find cycle basis
    vector<vi> final_paths;
    int min_cost = INT_MAX;
    rep(_,0,20) update_cycle_basis(final_paths, min_cost, edges, rng, edge_hash_to_index);

    // print cycles (by closing the paths)
    std::cout << final_paths.size() << '\n';
    for (vi& path : final_paths) {
        std::cout << path.size()+1 << ' ';
        for (int u : path) std::cout << u+1 << ' ';
        std::cout << path[0]+1; // cycle is a cycle, so it ends where it starts
        std::cout << '\n';
    }
}