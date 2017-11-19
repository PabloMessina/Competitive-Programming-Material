// tags: graph traversal, LCA, BFS, DFS, domain compression
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define umap unordered_map
using namespace std;
typedef pair<int,int> ii;
typedef vector<int> vi;

const int MAXN = 20000; // 2 * 10^4
int M, Q, N;

// -- map 1D coordinate values to id's in a compact range
umap<int, int> coord2id;
int ID;
int getId(int x) {
    auto it = coord2id.find(x);
    if (it == coord2id.end())
        return coord2id[x] = ID++;
    return it->second;
}

vector<vector<ii>> g; // original graph
int node_values[MAXN]; // store known values for nodes

// propagate known values to the whole connected component
void bfs(int s) {
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto& i : g[u]) {
            int v = i.first;
            if (node_values[v] == INT_MAX) {
                node_values[v] = i.second - node_values[u];
                q.push(v);
            }
        }
    }
}

int depth1[MAXN]; // store depths in graph 'g'
int parent[MAXN]; // store parents in graph 'g'
int anom_up[MAXN]; // store anomalie in the edge connecting with parent (upward)
bool dfs1(int u, int p, int d) {
    parent[u] = p;
    depth1[u] = d;
    for (auto& i : g[u]) {
        int v = i.first;
        if (v == p) continue;
        if (depth1[v] == -1) {
            anom_up[v] = i.second;
            if (dfs1(v, u, d+1)) {
                return true;
            }
        } else { // back-edge
            if ((depth1[u] - depth1[v]) % 2 == 0) { // odd-length
                int val = i.second;
                int cur = u;
                int coef = -1;
                while (1) {
                    int par = parent[cur];
                    val += coef * anom_up[cur];
                    if (par == v) break;
                    coef *= -1;
                    cur = par;
                }
                node_values[v] = val >> 1;
                bfs(v);
                return true;
            }
        }
    }
    return false;
}

vector<vi> tree; // tree used for LCA queries
// -- map old ids to new ids in an even more compact range
int ID2;
unordered_map<int,int> u2id;
int getId2(int u) {
    auto it = u2id.find(u);
    if (it == u2id.end())
        return u2id[u] = ID2++;
    return it->second;
}

int depth2[MAXN+1]; // store depths in 'tree'
int accsum[MAXN+1]; // store accumulated sums from sub-roots in 'tree'
// --- progressively build 'tree' from the original graph 'g'
// and update 'depth2' and 'accsum' along the way
void dfs2(int u, int d, int sum) {
    int uid = getId2(u);
    depth2[uid] = d;
    accsum[uid] = sum;
    for (auto& i : g[u]) {
        int v = i.first;
        int vid = getId2(v);
        if (depth2[vid] == -1) {
            tree[uid].push_back(vid);
            int nextsum = sum + ((d&1) ? -i.second : i.second);
            dfs2(v, d+1, nextsum);
        }
    }
}

inline int log2(int x) {
    return sizeof(int) * 8 - __builtin_clz(x) - 1;
}

namespace LCA {
    const int MAXNN = (MAXN+1)*2;
    const int MAXLOG = sizeof(int) * 8 - __builtin_clz(MAXNN);    
    int rmq[MAXNN][MAXLOG];
    int E[MAXNN];
    int D[MAXNN];
    int H[MAXN];
    int idx;
    vector<vi> *g;
    void dfs(int u, int d) {
        H[u] = idx;
        E[idx] = u;
        D[idx++] = d;
        for (int v : (*g)[u]) {
            if (H[v] == -1) {
                dfs(v, d+1);
                E[idx] = u;
                D[idx++] = d;
            }
        }
    }
    int find_lca(int u, int v) {
        int l = H[u], r = H[v];
        if (l > r) swap(l, r);
        int len = r - l + 1;
        int m = log2(len);
        int i1 = rmq[l][m];
        int i2 = rmq[r - ((1 << m) - 1)][m];
        return D[i1] < D[i2] ? E[i1] : E[i2];
    }
    void init(vector<vi> &_g) {
        g = &_g;
        int n = _g.size();
        memset(H, -1, sizeof(int)*n);

        idx = 0;
        dfs(0, 0); // euler tour
        int nn = idx;
        int m = log2(nn);

        // build sparse table with bottom-up DP
        rep(i,0,nn-1) rmq[i][0] = i; // base case
        rep(j,1,m) { // other cases
            rep(i, 0, nn - (1 << j)) {
                int i1 = rmq[i][j-1];
                int i2 = rmq[i + (1 << (j-1))][j-1];
                rmq[i][j] = D[i1] < D[i2] ? i1 : i2;
            }
        }
    }
}

int main() {
    while(1) {
        scanf("%d%d", &M, &Q);
        if (M==0 and Q==0) break;

        // reset variables
        g.assign(2 * M, vector<ii>());
        rep(i, 0, 2 * M -1) node_values[i] = INT_MAX;
        coord2id.clear();
        ID = 0;
        vector<int> diag;
        diag.reserve(2 * M);

        // read measurements
        while(M--) {
            int x,y,a;
            scanf("%d%d%d", &x,&y,&a);
            if (x == y) { // measurement at the diagonal
                int u = getId(x);
                node_values[u] = a;
                diag.push_back(u);
            } else { // general case: x + y = a
                int u = getId(x);
                int v = getId(y);
                g[u].emplace_back(v,a);
                g[v].emplace_back(u,a);
            }
        }
        N = ID; // set number of distinct nodes in the graph

        // ---------------
        // STEP 1: propagate known values at the diagonal
        for (int u : diag) bfs(u);

        // ---------------
        // STEP 2: find odd-length loops, solve equation system and propagate.
        // Also build tree encompassing those connected components without odd-length loops

        // reset variables
        memset(depth1, -1, sizeof(int) * N);
        memset(parent, -1, sizeof(int) * N);
        tree.assign(N+1, vi()); // make tree big enough
        memset(depth2, -1, sizeof(int) * (N+1));
        memset(accsum, 0, sizeof(int) * (N+1));
        u2id.clear();
        ID2 = 1; // id = 0 is reserved for the global root
        rep(u, 0, N-1) {
            if (node_values[u] == INT_MAX and depth1[u] == -1) {
                if (!dfs1(u, -1, 0)) { // no odd-length loops, this is a bipartite subgraph
                    tree[0].push_back(getId2(u)); // 0 is the root of all sub-roots
                    dfs2(u, 0, 0);
                }
            }
        }
        tree.resize(ID2); // remove unnecessary space

        // --- STEP 3: build LCA structure over 'tree' which includes all
        // bipartite connected components (no odd-length loops) of 'g'
        LCA::init(tree);
        
        // ----------------
        // answer queries
        while (Q--) {
            int x, y; scanf("%d%d", &x, &y);
            int u = getId(x);
            int v = getId(y);

            // printf("query: x=%d, y=%d, u=%d, v=%d\n",x,y,u,v);
            if (u >= N or v >= N) { // outside range
                puts("*");
                continue; 
            }
            if (u == v) { // diagonal point
                if (node_values[u] == INT_MAX) { // value unknown
                    puts("*");
                } else { // value known
                    printf("%d\n", node_values[u]);
                }
            } else { // non-diagonal point
                int uval = node_values[u];
                int vval = node_values[v];
                if (uval != INT_MAX and vval != INT_MAX) {
                    // both values known
                    printf("%d\n", uval + vval);
                } else if ((uval != vval) and (uval == INT_MAX or vval == INT_MAX)) {
                    // one value known but the other is unknown
                    puts("*");
                } else { // both unknown -> use LCA
                    int uu = getId2(u);
                    int vv = getId2(v);
                    int lca = LCA::find_lca(uu, vv);
                    if (lca == 0) { // 0 is the lca, so u and v belong to different connected components
                        puts("*");
                    } else { // u and v are in the same connected component
                        int path_length = depth2[uu] + depth2[vv] - 2 * depth2[lca];
                        if (path_length & 1) { // odd
                            int u_sum = accsum[uu] - accsum[lca];
                            int v_sum = accsum[vv] - accsum[lca];
                            if ((depth2[uu] & 1) == 0) u_sum = -u_sum;
                            if ((depth2[vv] & 1) == 0) v_sum = -v_sum;
                            printf("%d\n", u_sum + v_sum);
                        } else { // even
                            puts("*");
                        }
                    }
                }
            }
        }
        puts("-");
    }
    return 0;
}