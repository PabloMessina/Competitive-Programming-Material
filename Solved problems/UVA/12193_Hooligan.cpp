// tags: max flow, Dinic
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------
struct Dinic {
    struct Edge { int to, rev; ll f, c; };
    int n, t_; vector<vector<Edge>> G;
    vector<ll> D;
    vector<int> q, W;
    bool bfs(int s, int t) {
        W.assign(n, 0); D.assign(n, -1); D[s] = 0;
        int f = 0, l = 0; q[l++] = s;
        while (f < l) {
            int u = q[f++];
            for (const Edge &e : G[u]) if (D[e.to] == -1 && e.f < e.c)
                D[e.to] = D[u] + 1, q[l++] = e.to;
        }
        return D[t] != -1;
    }
    ll dfs(int u, ll f) {
        if (u == t_) return f;
        for (int &i = W[u]; i < (int)G[u].size(); ++i) {
            Edge &e = G[u][i]; int v = e.to;
            if (e.c <= e.f || D[v] != D[u] + 1) continue;
            ll df = dfs(v, min(f, e.c - e.f));
            if (df > 0) { e.f += df, G[v][e.rev].f -= df; return df; }
        }
        return 0;
    }
    Dinic(int N) : n(N), G(N), D(N), q(N) {}
    void add_edge(int u, int v, ll cap) {
        G[u].push_back({v, (int)G[v].size(), 0, cap});
        G[v].push_back({u, (int)G[u].size() - 1, 0, 0});
    }
    ll max_flow(int s, int t) {
        t_ = t; ll ans = 0;
        while (bfs(s, t)) while (ll dl = dfs(s, LLONG_MAX)) ans += dl;
        return ans;
    }
};
umap<int,int> x2id;
int ID = 0;
int get_id(int x) {
    auto it = x2id.find(x);
    if (it == x2id.end()) return x2id[x] = ID++;
    return it->second;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M, G;
    nextcase:
    while (cin >> N >> M >> G and N) {
        vector<int> P(N, 0);
        vector<int> C(N * N, 0);
        rep(_,0,G) {
            int i, j; char c; cin >> i >> c >> j;
            if (c == '=') P[i]++, P[j]++;
            else if (c == '>') P[i] += 2;
            else P[j] += 2;
            if (i > j) swap (i, j);
            C[i * N + j]++;
        }
        rep(i,1,N) P[0] += (M - C[i]) * 2;
        rep(i,1,N) if (P[i] >= P[0]) {
            cout << "N\n";
            goto nextcase;
        }
        ID = 0;
        x2id.clear();
        Dinic din((N-1)*(N-2)/2 + N-1 + 2);
        int s = get_id(-1), t = get_id(-2);
        int tot_pts = 0;
        rep(i,1,N) rep(j,i+1,N) {
            int u = get_id(i * N + j);
            int ii = get_id(N * N + i);
            int jj = get_id(N * N + j);
            int pts = (M - C[i * N + j])*2;
            tot_pts += pts;
            din.add_edge(s, u, pts);
            din.add_edge(u, ii, pts);
            din.add_edge(u, jj, pts);            
        }
        rep(i,1,N) din.add_edge(get_id(N * N + i), t, P[0] - P[i] - 1);
        if (din.max_flow(s,t) == tot_pts) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }
    return 0;
}