// tags: LCA, jump pointers, binary lifting, tree diameter, sparse tables
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

namespace LCA {
    const int MAXN = 5 * 100000 * 2 + 4;
    const int MAXLOG = 31 - __builtin_clz(MAXN);
    int P[MAXN][MAXLOG+1];
    int D[MAXN];
    int n = 4;
    void init() {
        memset(P, -1, sizeof P);
        D[0] = 0;
        rep(u,1,3) {
            P[u][0] = 0;
            D[u] = 1;
        }
    }
    void add_child(int p) {
        P[n][0] = p;
        D[n] = D[p] + 1;
        rep(i,1,MAXLOG) {
            p = P[p][i-1];
            if (p == -1) break;
            P[n][i] = p;
        }
        n++;
    }
    int raise(int u, int dist) {
        for (int i = 0; dist; i++, dist>>=1) if (dist&1) u = P[u][i];
        return u;
    }
    int get_lca(int u, int v) {        
        if (D[u] < D[v]) swap(u, v);
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

int main() {
    int q; scanf("%d", &q);
    int diam = 2;
    int e1 = 1, e2 = 2;
    LCA::init();
    while(q--) {
        int u; scanf("%d", &u); u--;
        int far_e, far_dist;
        int d1 = LCA::dist(u, e1);
        int d2 = LCA::dist(u, e2);
        if (d1 > d2) {
            far_e = e1;
            far_dist = d1;            
        } else {
            far_e = e2;
            far_dist = d2;
        }
        if (far_dist == diam) {
            diam = far_dist + 1;
            e1 = far_e;
            e2 = LCA::n;            
        }
        LCA::add_child(u);
        LCA::add_child(u);
        printf("%d\n", diam);
    }
    return 0;
}