/* ============================ */
/* LCA (Lowest Common Ancestor) */
/* ============================ */
#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;
#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,b,a) for (int i=b; i>=a; --i)

// -----------------------------------
// METHOD 1: SPARSE TABLE - EULER TOUR
// -----------------------------------
// construction: O(2|V| log 2|V|) = O(|V| log |V|)
// query: O(1)  
// cannot be updated :(

namespace LCA1 {
    const int MAXN = 10000;
    const int MAXLOG = sizeof(int) * 8 - __builtin_clz(MAXN);

    int E[2 * MAXN]; // records sequence of visited nodes
    int D[2 * MAXN]; // records depth of each visited node
    int H[MAXN]; // records index of first ocurrence of node u in E
    int idx; // tracks node ocurrences
    int rmq[2 * MAXN][MAXLOG]; // memo table for range minimun query
    vector<vi> *g; // pointer to graph
    int n; // number of nodes
    int root; // root of the tree

    // get highest exponent e such that 2^e <= x
    inline int log2(int x) { return sizeof(x) * 8 - __builtin_clz(x) - 1; }

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

    void init(vector<vi> &_g, int _root) {
        g = &_g;
        root = _root;
        n = _g.size();
        memset(H, -1, sizeof(int)*n);
        idx = 0;
        dfs(root, 0); // euler tour
        int nn = idx; // <-- make sure you use the correct number  
        int m = log2(nn);
        // build sparse table with bottom-up DP
        rep(i,0,nn-1) rmq[i][0] = i; // base case
        rep(j,1,m) { // other cases
            rep(i, 0, nn - (1 << j)) {
                // i ... i + 2 ^ (j-1) - 1
                int i1 = rmq[i][j-1];
                // i + 2 ^ (j-1) ... i + 2 ^ j  - 1
                int i2 = rmq[i + (1 << (j-1))][j-1];
                // choose index with minimum depth
                rmq[i][j] = D[i1] < D[i2] ? i1 : i2;
            }
        }
    }

    int find_lca(int u, int v) {
        // get ocurrence indexes in increasing order
        int l = H[u], r = H[v];
        if (l > r) swap(l, r);
        // get node with minimum depth in range [l .. r] in O(1)
        int len = r - l + 1;
        int m = log2(len);
        int i1 = rmq[l][m];
        int i2 = rmq[r - ((1 << m) - 1)][m];
        return D[i1] < D[i2] ? E[i1] : E[i2];
    }

    int dist(int u, int v) {
        // make sure you use H to retrieve the indexes of u and v
        // within the Euler Tour sequence before using D
        return D[H[u]] + D[H[v]] - 2 * D[H[find_lca(u,v)]];
    }    
}

// ---------------------------------------
// METHOD 2: SPARSE TABLE - JUMP POINTERS
// ----------------------------------------
// construction: O(|V| log |V|)
// query: O(log|V|)
// can be updated: tree can receive new nodes :)

namespace LCA2 {
    const int MAXN = 1000000;
    const int MAXLOG = sizeof(int) * 8 - __builtin_clz(MAXN);

    int P[MAXN][MAXLOG+1]; // level ancestor table
    int D[MAXN]; // depths
    int n; // num of nodes
    vector<vi> *g; // pointer to graph
    int root; // root of the tree

    // get highest exponent e such that 2^e <= x
    inline int log2(int x) { return sizeof(x) * 8 - __builtin_clz(x) - 1; }

    // dfs to record direct parents and depths
    void dfs(int u, int p, int depth) {
        P[u][0] = p;
        D[u] = depth;        
        for (int v : (*g)[u]) {
            if (D[v] == -1) {
                dfs(v, u, depth + 1);
            }
        }
    }

    void init(vector<vi> &_g, int _root) {
        g = &_g;
        root = _root;
        n = _g.size();
        memset(P, -1, sizeof(int) * n);
        memset(D, -1, sizeof(int) * n);        
        dfs(root, -1, 0);
        rep(j, 1, MAXLOG) {
            rep (i, 0, n-1) {
                // i's 2^j th ancestor is
                // i's 2^(j-1) th ancestor's 2^(j-1) th ancestor
                int p = P[i][j-1];
                if (p != -1) P[i][j] = P[p][j-1];
            }
        }
    }

    int find_lca(int u, int v) {
        if (D[u] < D[v]) swap(u, v);
        // raise lowest to same level
        int diff = D[u] - D[v];
        while (diff) {
            int j = log2(diff);
            u = P[u][j];
            diff -= (1 << j);
        }
        if (u == v) return u; // same node, we are done
        // raise u and v to their highest ancestors below the LCA
        invrep (j, MAXLOG, 0) {
            // if there are 2^j th ancestors for u and v and they are not the same,
            // then they can be raised and still be below the LCA
            if (P[u][j] != -1 && P[u][j] != P[v][j]) {
                u = P[u][j], v = P[v][j];
            }
        }
        // the direct parent of u (or v) is lca(u,v)
        return P[u][0];
    }

    int dist(int u, int v) {
        return D[u] + D[v] - 2 * D[find_lca(u,v)];
    }

    int add_child(int u, int v) {
        // add to graph
        (*g)[u].push_back(v);
        // update depth
        D[v] = D[u] + 1;
        // update ancestors
        P[v][0] = u;
        rep (j, 1, MAXLOG){
            P[v][j] = P[P[v][j-1]][j-1];
            if (P[v][j] == -1) break;
        }
    }
}