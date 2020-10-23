// tags: max flow, dinic
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
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
        G[v].push_back({u, (int)G[u].size() - 1, 0, 0}); // Use cap instead of 0 if bidirectional
    }
    ll max_flow(int s, int t) {
        t_ = t; ll ans = 0;
        while (bfs(s, t)) while (ll dl = dfs(s, LLONG_MAX)) ans += dl;
        return ans;
    }
};
const int MAXN = 100;
int N;
vector<string> board;
int rows[MAXN][MAXN], cols[MAXN][MAXN];
int ID = 0;
map<int, int> x2id;
int get_id(int x) {
    auto it = x2id.find(x);
    if (it == x2id.end()) return x2id[x] = ID++;
    return it->second;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N) {
        board.resize(N);
        rep(i,0,N) cin >> board[i];
        ID = 0;
        set<int> row_ids, col_ids;
        rep(r,0,N) {
            rep(c,0,N) {
                if (board[r][c] == '.') {
                    rows[r][c] = ID;
                    row_ids.insert(ID);
                } else ++ID;
            }
            ++ID;
        }
        rep(c,0,N) {
            rep(r,0,N) {
                if (board[r][c] == '.') {
                    cols[r][c] = ID;
                    col_ids.insert(ID);
                } else ++ID;
            }
            ++ID;
        }
        Dinic din(row_ids.size() + col_ids.size() + 2);
        ID = 0; x2id.clear();
        int s = get_id(-1), t = get_id(-2);
        for (int x : row_ids) din.add_edge(s, get_id(x), 1);
        for (int x : col_ids) din.add_edge(get_id(x), t, 1);
        rep(r,0,N) rep(c,0,N) {
            if (board[r][c] == '.') {
                int u = get_id(rows[r][c]);
                int v = get_id(cols[r][c]);
                din.add_edge(u, v, 1);
            }
        }
        cout << din.max_flow(s,t) << '\n';
    }
    return 0;
}