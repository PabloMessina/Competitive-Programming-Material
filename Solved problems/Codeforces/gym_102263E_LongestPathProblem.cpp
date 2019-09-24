// TODO: optimize this, TLE on test case 60 :(
// tags: DP, trees, LCA, binary lifting, diameters, binary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
const int MAXN = 200000;
int N;
vector<vector<tuple<int,ll,int>>> g;
struct Edge {
    int u, v; ll w;
    Edge (int u, int v, ll w) : u(u), v(v), w(w) {}
};
vector<Edge> edges;

struct LCA {
    vector<int> A, D;
    vector<ll> accW;
    int n, maxe;
    int& anc(int u, int e) { return A[e * n + u]; }    
    int inline log2(int x) { return 31 - __builtin_clz(x); }

    void dfs(int u, int p, int depth, ll accw) {
        anc(u,0) = p;
        D[u] = depth;
        accW[u] = accw;
        for (auto& x : g[u]) {
            int v = get<0>(x);
            ll w = get<1>(x);
            if (D[v] == -1) {
                dfs(v, u, depth + 1, accw + w);
            }
        }
    }
    LCA() {}
    LCA(int root) {
        n = g.size();
        maxe = log2(n);
        D.assign(n, -1);
        accW.resize(n);
        A.resize(n * (maxe + 1));
        dfs(root, -1, 0, 0);
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
    ll steps_dist(int u, int v, int lca) {
        return D[u] + D[v] - 2 * D[lca];
    }
    ll weight_dist(int u, int v) {
        return accW[u] + accW[v] - 2 * accW[lca(u,v)];
    }
    ll weight_dist(int u, int v, int lca) {
        return accW[u] + accW[v] - 2 * accW[lca];
    }
    pair<int, ll> get_kth_node_and_dist_in_path(int k, int u, int v, int lca_uv, int steps) {
        if (D[u] - D[lca_uv] >= k) {
            int x = raise(u, k);
            return { x, weight_dist(u, x, x) };
        }
        int x = raise(v, steps - k);
        return { x, weight_dist(u, x, lca_uv) };
    }
} lca;


pair<int,int> memo_diam_ends[MAXN][2];
ll memo_diam[MAXN][2];
ll memo_depth[MAXN][2];
int memo_leaf[MAXN][2];

void DP(int i, int d) {
    ll& max_diam = memo_diam[i][d];
    if (max_diam != -1) return;
    
    ll& max_depth = memo_depth[i][d];
    int& max_depth_leaf = memo_leaf[i][d];
    auto& diam_ends = memo_diam_ends[i][d];
    Edge& e = edges[i];

    int p = e.u, u = e.v;
    if (d == 1) swap(u, p);
    max_depth = 0;
    max_depth_leaf = u;
    max_diam = 0;
    ll depth1 = 0, depth2 = 0;
    int leaf1 = u, leaf2 = u;
    diam_ends = { u, u };

    for (auto& x : g[u]) {
        int v; ll w; int ii;
        tie(v,w,ii) = x;
        if (v == p) continue;
        int dd = (u == edges[ii].u) ? 0 : 1;
        DP(ii, dd);

        ll diam = memo_diam[ii][dd];
        if (max_diam < diam) {
            max_diam = diam;
            diam_ends = memo_diam_ends[ii][dd];
        }

        ll depth = memo_depth[ii][dd] + w;
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

    ll leaf_dist = lca.weight_dist(leaf1, leaf2);
    if (leaf_dist > max_diam) {
        max_diam = leaf_dist;
        diam_ends = { leaf1, leaf2 };
    }
}

ll middle_dist(int u, int v) {
    int lca_uv = lca.lca(u, v);
    int steps = lca.steps_dist(u,v,lca_uv);
    ll dist =  lca.weight_dist(u,v,lca_uv);
    int l = 0, r = steps+1;
    int mu; ll md;
    while (l < r) {
        int m = (l+r) >> 1;
        tie(mu, md) = lca.get_kth_node_and_dist_in_path(m, u, v, lca_uv, steps);
        if (md >= dist - md) r = m;
        else l = m+1;
    }
    tie(mu, md) = lca.get_kth_node_and_dist_in_path(l, u, v, lca_uv, steps);
    ll ans = max(md, dist - md);
    if (l > 0) {
        tie(mu, md) = lca.get_kth_node_and_dist_in_path(l-1, u, v, lca_uv, steps);
        ans = min(ans, max(md, dist - md));
    }
    return ans;
}

int main() {
    scanf("%d", &N);
    g.resize(N);    
    rep(i,0,N-2) {
        int u, v; ll w;
        scanf("%d %d %lld", &u, &v, &w);
        --u, --v;
        g[u].emplace_back(v,w,i);
        g[v].emplace_back(u,w,i);
        edges.emplace_back(u,v,w);
    }
    lca = LCA(0);
    memset(memo_diam, -1, sizeof memo_diam);
    rep(i,0,N-2) {
        DP(i,0), DP(i,1);
        ll diam = max(memo_diam[i][0], memo_diam[i][1]);
        int u, v;        
        tie(u,v) = memo_diam_ends[i][0];        
        ll d0 = middle_dist(u,v);
        tie(u,v) = memo_diam_ends[i][1];
        ll d1 = middle_dist(u,v);
        diam = max(diam, d0 + d1 + edges[i].w);
        printf("%lld\n", diam);
    }
    return 0;
}