/* ============================ */
/* LCA (Lowest Common Ancestor) */
/* ============================ */
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for (int i=a; i<b; ++i)
#define invrep(i,b,a) for (int i=b; i>=a; --i)

// General comments:
// * Both of these methods assume that we are working with a connected
//   graph 'g' of 'n' nodes, and that nodes are compactly indexed from 0 to n-1.
//   In case you have a forest of trees, a simple trick is to create a fake
//   root and connect all the trees to it (make sure to re-index all your nodes)
// * 'g' need not be a 'tree', DFS fill implictly find a tree for you
//   in case you don't care of the specific tree (e.g. if cycles are not important)

// ------------------------------------------------------------
// METHOD 1: SPARSE TABLE - BINARY LIFTING (aka JUMP POINTERS)
// ------------------------------------------------------------
// construction: O(|V| log |V|)
// query: O(log|V|)
// ** advantages:
//   - the lca query can be modified to compute querys over the path between 2 nodes
//   - it's possible to append new leaf nodes to the tree
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
    // distance between 'u' and 'v'
    int dist(int u, int v) {
        return D[u] + D[v] - 2 * D[lca(u,v)];
    }
    // optimized version (in case you already computed lca(u,v))
    int dist(int u, int v, int lca_uv) {
        return D[u] + D[v] - 2 * D[lca_uv];
    }
    // get the node located k steps from 'u' walking towards 'v'
    int kth_node_in_path(int u, int v, int k) {
        int lca_uv = lca(u,v);
        if (D[u] - D[lca_uv] >= k) return raise(u, k);
        return raise(v, dist(u,v,lca_uv) - k);
    }
    int add_child(int p, int u) { // optional
        // add to graph
        (*g)[p].push_back(u);
        // update depth
        D[u] = D[p] + 1;
        // update ancestors
        anc(u,0) = p;
        rep(e,1,maxe){
            p = anc(p,e-1);
            if (p == -1) break;
            anc(u,e) = p;
        }
    }
};

// ------------------------------------------
// METHOD 2: SPARSE TABLE - EULER TOUR + RMQ
// ------------------------------------------
// construction: O(2|V| log 2|V|) = O(|V| log |V|)
// query: O(1) (** assuming that __builtin_clz is mapped to an
//               efficient processor instruction)
struct LCA {
    vector<int> E, D, H; // E = euler tour, D = depth, H = first index of node in euler tour
    vector<int> DP // memo for range minimun query
    vector<vector<int>> *g; // pointer to graph
    int idx; // tracks node ocurrences
    int n; // number of nodes
    int& rmq(int i, int e) { return DP[e * idx + i]; }
    inline int log2(int x) { return 31 - __builtin_clz(x); }
    void dfs(int u, int depth) {
        H[u] = idx; // index of first u's ocurrence
        E[idx] = u; // record node ocurrence
        D[idx++] = depth; // record depth
        for (int v : (*g)[u]) {
            if (H[v] == -1) {
                dfs(v, depth + 1); // explore v's subtree and come back to u
                E[idx] = u; // new ocurrence of u
                D[idx++] = depth;
            }
        }
    }
    LCA(vector<vector<int>>& _g, int root) {
        g = &_g;
        n = _g.size();
        H.assign(n, -1);
        E.resize(2*n);
        D.resize(2*n);
        idx = 0;
        dfs(root, 0); // euler tour
        int nn = idx; // <-- make sure you use the correct number  
        int maxe = log2(nn);
        DP.resize(nn * (maxe+1));        
        // build sparse table with bottom-up DP
        rep(i,0,nn) rmq(i,0) = i; // base case
        rep(e,1,maxe+1) { // general cases
            rep(i,0,nn-(1<<e)+1) {
                // i ... i + 2 ^ (e-1) - 1
                int i1 = rmq(i,e-1);
                // i + 2 ^ (e-1) ... i + 2 ^ e  - 1
                int i2 = rmq(i + (1 << (e-1)), e-1);
                // choose index with minimum depth
                rmq(i,e) = D[i1] < D[i2] ? i1 : i2;
            }
        }
    }
    int lca(int u, int v) {
        // get ocurrence indexes in increasing order
        int l = H[u], r = H[v];
        if (l > r) swap(l, r);
        // get node with minimum depth in range [l .. r] in O(1)
        int len = r - l + 1;
        int e = log2(len);
        int i1 = rmq(l,e);
        int i2 = rmq(r - ((1 << e) - 1), e);
        return D[i1] < D[i2] ? E[i1] : E[i2];
    }
    int dist(int u, int v) {
        // make sure you use H to retrieve the indexes of u and v
        // within the Euler Tour sequence before using D
        return D[H[u]] + D[H[v]] - 2 * D[H[lca(u,v)]];
    }
}

// -----------------
// EXAMPLE OF USAGE
// -----------------
int main() {
    // build graph
    int n, m; cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int u, v; cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    // init LCA
    LCA lca(g,0);
    // answer queries
    int q; cin >> q;
    while (q--) {
        int u, v; cin >> u >> v;
        cout << "LCA(" << u << "," << v << ") = " << lca.lca(u,v) << '\n';
        cout << "dist(" << u << "," << v << ") = " << lca.dist(u,v) << '\n';
    }
};