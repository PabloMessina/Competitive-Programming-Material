// tags: LCA, LA, level ancestor, jump pointers, binary lifting, tree diameter
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 20000;
vi g[MAXN];
int n;

namespace LCA {
    const int MAXLOG = 31 - __builtin_clz(MAXN);
    int P[MAXN][MAXLOG+1];
    int D[MAXN];
    void dfs(int u, int p, int d) {
        P[u][0] = p;
        D[u] = d;
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u, d+1);
        }
    }
    void init() {
        dfs(0, -1, 0);
        rep(i,1,MAXLOG) {
            rep(u,0,n-1) {
                int p = P[u][i-1];
                if (p == -1) P[u][i] = -1;
                else P[u][i] = P[p][i-1];
            }
        }
    }
    int raise(int u, int dist) {
        for (int i=0; dist; dist>>=1, i++) if (dist&1) u = P[u][i];
        return u;
    }
    int get_lca(int u, int v) {
        if (D[u] < D[v]) swap(u,v);
        u = raise(u, D[u] - D[v]);
        if (u == v) return u;
        invrep(i, MAXLOG, 0) {
            if (P[u][i] != P[v][i]) {
                u = P[u][i], v = P[v][i];
            }
        }
        return P[u][0];
    }
    int dist(int u, int v) {
        return D[u] + D[v] - 2 * D[get_lca(u,v)];
    }
}

int farthest_from(int s) {
    static int dist[MAXN];
    memset(dist, -1, sizeof(int) * n);
    queue<int> q;
    q.push(s);
    dist[s] = 0;
    int farthest = s;
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = 1 + dist[u];
                q.push(v);
                if (dist[v] > dist[farthest]) farthest = v;                
            }
        }
    }
    return farthest;
}

int main() {
    int q;
    scanf("%d%d", &n, &q);
    rep(_,2,n) {
        int u,v; scanf("%d%d",&u,&v); --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    LCA::init();
    int e1 = farthest_from(0);
    int e2 = farthest_from(e1);
    int diam = LCA::dist(e1, e2);
    while (q--) {
        int v, d; scanf("%d%d", &v, &d); --v;
        if (d > diam) {
            puts("0");
            continue;
        }
        int e, e_dist;
        int d1 = LCA::dist(v, e1);
        int d2 = LCA::dist(v, e2);
        if (d1 > d2) {
            e = e1; e_dist = d1;
        } else {
            e = e2; e_dist = d2;
        }
        if (d > e_dist) {
            puts("0");
            continue;
        }
        int lca = LCA::get_lca(v, e);
        int v_lca_dist = LCA::D[v] - LCA::D[lca];
        int u;
        if (d <= v_lca_dist) {
            u = LCA::raise(v, d);
        } else {
            u = LCA::raise(e, e_dist - d);
        }
        printf("%d\n", u+1);
    }
    return 0;
}