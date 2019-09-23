// tags: DP, trees, LCA, binary lifting, diameters
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100000;
int N;
vector<vector<pair<int,int>>> g;

struct LCA {
    vector<int> A, D;
    int n, maxe;
    int& anc(int u, int e) { return A[e * n + u]; }    
    int inline log2(int x) { return 31 - __builtin_clz(x); }
    void dfs(int u, int p, int depth) {
        anc(u,0) = p;
        D[u] = depth;        
        for (auto& x : g[u]) {
            int v = get<0>(x);
            if (D[v] == -1) {
                dfs(v, u, depth + 1);
            }
        }
    }
    LCA() {}
    LCA(int root) {
        n = g.size();
        maxe = log2(n);
        D.assign(n, -1);
        A.resize(n * (maxe + 1));
        dfs(root, -1, 0);
        rep(e, 1, maxe) {
            rep (u, 0, n-1) {
                int a = anc(u,e-1);
                anc(u,e) = (a == -1 ? -1 : anc(a,e-1));
            }
        }
    }
    int raise(int u, int k) {
        for (int e = 0; k; e++, k>>=1) if (k&1) u = anc(u,e);
        return u;
    }
    int lca(int u, int v) {        
        if (D[u] < D[v]) swap(u, v); 
        u = raise(u, D[u] - D[v]);
        if (u == v) return u;
        invrep (e, maxe, 0) {
            if (anc(u,e) != anc(v,e)) {
                u = anc(u,e), v = anc(v,e);
            }
        }
        return anc(u,0);
    }
    int dist(int u, int v) {
        return D[u] + D[v] - 2 * D[lca(u,v)];
    }
    int dist(int u, int v, int lca_uv) {
        return D[u] + D[v] - 2 * D[lca_uv];
    }
    int kth_node_in_path(int u, int v, int k) {
        int lca_uv = lca(u,v);
        if (D[u] - D[lca_uv] >= k) return raise(u, k);
        return raise(v, dist(u,v,lca_uv) - k);
    }
} lca;

struct Edge { int u, v; };
vector<Edge> edges;

int memo_diam[MAXN][2];
int memo_depth[MAXN][2];
int memo_leaf[MAXN][2];
pair<int,int> memo_diam_ends[MAXN][2];
void DP(int i, int d) {
    int& max_diam = memo_diam[i][d];
    if (max_diam != -1) return;
    
    int& max_depth = memo_depth[i][d];
    int& max_depth_leaf = memo_leaf[i][d];
    auto& diam_ends = memo_diam_ends[i][d];
    Edge& e = edges[i];

    int p = e.u, u = e.v;
    if (d == 1) swap(u, p);
    max_depth = 0;
    max_depth_leaf = u;
    max_diam = 0;
    int depth1 = 0, depth2 = 0;
    int leaf1 = u, leaf2 = u;
    diam_ends = { u, u };

    for (auto& x : g[u]) {
        int v, ii; tie(v,ii) = x;
        if (v == p) continue;
        int dd = (u == edges[ii].u) ? 0 : 1;
        DP(ii, dd);

        int diam = memo_diam[ii][dd];
        if (max_diam < diam) {
            max_diam = diam;
            diam_ends = memo_diam_ends[ii][dd];
        }

        int depth = memo_depth[ii][dd] + 1;
        if (max_depth < depth) {
            max_depth = depth;
            max_depth_leaf = memo_leaf[ii][dd];
        }

        if (depth1 < depth) {
            depth2 = depth1;
            depth1 = depth;
            leaf2 = leaf1;
            leaf1 = memo_leaf[ii][dd];
        } else if (depth2 < depth) {
            depth2 = depth;
            leaf2 = memo_leaf[ii][dd];
        }
    }

    int leaf_dist = lca.dist(leaf1, leaf2);
    if (leaf_dist > max_diam) {
        max_diam = leaf_dist;
        diam_ends = { leaf1, leaf2 };
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    g.resize(N);
    map<pair<int,int>,int> edge2index;
    rep(i,0,N-2) {
        int u, v; cin >> u >> v; --u, --v;
        g[u].emplace_back(v,i);
        g[v].emplace_back(u,i);
        edge2index[{u,v}] = i;
        edge2index[{v,u}] = i;
        edges.push_back({u,v});
    }
    lca = LCA(0);
    memset(memo_diam, -1, sizeof memo_diam);
    int Q; cin >> Q;
    while (Q--) {
        int u, v; cin >> u >> v; --u, --v;

        int between = lca.dist(u, v) - 1;
        int mu = lca.kth_node_in_path(u, v, between/2);
        int mv = lca.kth_node_in_path(u, v, between/2 + 1);
        auto it = edge2index.find({mu, mv});
        int i = it->second;
        DP(i,0), DP(i,1);
        
        int d = (mu == edges[i].u) ? 0 : 1;
        auto pu = memo_diam_ends[i][1-d];
        auto pv = memo_diam_ends[i][d];
        int ans = max({ lca.dist(u,pu.first), lca.dist(u,pu.second),
                    lca.dist(v,pv.first), lca.dist(v,pv.second) });
        cout << ans << '\n';
    }
    return 0;
}