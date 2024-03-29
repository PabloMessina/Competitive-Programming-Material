// tags: LCA, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
struct LCA {
    vector<int> A, D;
    vector<vector<int>> *g;
    int n, maxe;
    int& anc(int u, int e) { return A[e * n + u]; }    
    int inline log2(int x) { return 31 - __builtin_clz(x); }

    void dfs(int u, int p, int depth) {
        anc(u,0) = p;
        D[u] = depth;        
        for (int v : (*g)[u]) {
            if (D[v] == -1) {
                dfs(v, u, depth + 1);
            }
        }
    }

    LCA(vector<vector<int>>& _g, int root) {
        g = &_g;
        n = _g.size();
        maxe = log2(n);
        D.assign(n, -1);
        A.resize(n * (maxe + 1));
        dfs(root, -1, 0);
        rep(e, 1, maxe+1) {
            rep(u, 0, n) {
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
        invrep(e, maxe, 0) {
            if (anc(u,e) != anc(v,e)) {
                u = anc(u,e), v = anc(v,e);
            }
        }
        return anc(u,0);
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    rep(t,0,T) {
        int N; cin >> N;
        vector<vector<int>> g(N);
        rep(u,0,N) {
            int m; cin >> m;
            while (m--) {
                int v; cin >> v; v--;
                g[u].push_back(v);
                g[v].push_back(u);
            }
        }
        LCA lca(g, 0);
        int Q; cin >> Q;
        cout << "Case " << t << ":\n";
        while (Q--) {
            int u, v; cin >> u >> v; --u, --v;
            cout << lca.lca(u,v) + 1 << '\n';
        }
    }
    return 0;
}