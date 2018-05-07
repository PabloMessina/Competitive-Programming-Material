// tags: LCA, level ancestor, jump pointers, sparse table
#include <bits/stdc++.h>
using namespace std;

#define MAXN 1000010
#define MAXLOG 20

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,b,a) for(int i=b; i>=a; --i)

int P[MAXN][MAXLOG+1];
int L[MAXN];
int e1, e2; // diameter's ends
int diam; // diameter's length
int n;

void init() {
    memset(P, -1, sizeof P);
    L[0] = 0;
    rep (i,1,3) P[i][0] = 0, L[i] = 1;
    e1 = 1;
    e2 = 2;
    diam = 2;
    n = 4;
}

int log2(int x) {
    int i = -1;
    while (x) x >>= 1, ++i;
    return i;
}

int lev_anc(int u, int k) {
    if (k == 0) return u;
    invrep(j, log2(k), 0) {
        if (k >= (1 << j)) {
            u = P[u][j];
            k -= (1 << j);
            if (k == 0) break;
        }
    }
    return u;
}

int LCA(int u, int v) {
    if (L[u] < L[v]) swap(u,v);
    int diff = L[u] - L[v];
    u = lev_anc(u, diff);
    if (u == v) return u;
    invrep(j, MAXLOG, 0)
        if ((P[u][j] != -1) and (P[u][j] != P[v][j]))
            u = P[u][j], v = P[v][j];
    return P[u][0];
}

int dist(int u, int v) {
    return L[u] + L[v] - 2 * L[LCA(u,v)];
}

int add_child(int u, int v) {
    // update level
    L[v] = L[u] + 1;
    // update ancestors
    P[v][0] = u;
    rep (j, 1, MAXLOG){
        P[v][j] = P[P[v][j-1]][j-1];
        if (P[v][j] == -1) break;
    }
}

int main () {
    init();

    int q; scanf("%d",&q);  
    while (q--) {
        int v; scanf("%d", &v); --v;
        // update diamater
        int d1 = dist(v, e1);
        int d2 = dist(v, e2);
        int maxd, f;
        if (d1 > d2)
            maxd = d1, f = e1;
        else
            maxd = d2, f = e2;
        if (maxd == diam) {
            diam++;
            e1 = f;
            e2 = n;
        }
        // add 2 children
        add_child(v, n);
        add_child(v, n+1);
        // update n
        n += 2;
        // answer
        printf("%d\n", diam);
    }
    return 0;
}