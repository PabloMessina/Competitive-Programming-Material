// tags: bipartite matching, maxflow, dinic
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------
int R, C;
vector<string> board;
int ID;
umap<int,int> x2id;
int get_id(int x) {
    auto it = x2id.find(x);
    if (it == x2id.end()) {
        return x2id[x] = ID++;
    }
    return it->second;
}

struct Dinic {
    struct edge {
        int to, rev;
        ll f, cap;
    };
 
    vector<vector<edge>> g;
    vector<ll> dist;
    vector<int> q, work;
    int n, sink;
 
    bool bfs(int start, int finish) {
        dist.assign(n, -1);
        dist[start] = 0;
        int head = 0, tail = 0;
        q[tail++] = start;
        while (head < tail) {
            int u = q[head++];
            for (const edge &e : g[u]) {
                int v = e.to;
                if (dist[v] == -1 and e.f < e.cap) {
                    dist[v] = dist[u] + 1;
                    q[tail++] = v;
                }
            }
        }
        return dist[finish] != -1;
    }
 
    ll dfs(int u, ll f) {
        if (u == sink)
            return f;
        for (int &i = work[u]; i < (int)g[u].size(); ++i) {
            edge &e = g[u][i];
            int v = e.to;
            if (e.cap <= e.f or dist[v] != dist[u] + 1)
                continue;
            ll df = dfs(v, min(f, e.cap - e.f));
            if (df > 0) {
                e.f += df;
                g[v][e.rev].f -= df;
                return df;
            }
        }
        return 0;
    }

    Dinic(int n) {
        this->n = n;
        g.resize(n);
        dist.resize(n);
        q.resize(n);
    }
 
    void add_edge(int u, int v, ll cap) {
        edge a = {v, (int)g[v].size(), 0, cap};
        edge b = {u, (int)g[u].size(), 0, 0}; //Poner cap en vez de 0 si la arista es bidireccional
        g[u].push_back(a);
        g[v].push_back(b);
    }
 
    ll max_flow(int source, int dest) {
        sink = dest;
        ll ans = 0;
        while (bfs(source, dest)) {
            work.assign(n, 0);
            while (ll delta = dfs(source, LLONG_MAX))
                ans += delta;
        }
        return ans;
    }
};

int movr[4] = {0, 1, 0, -1};
int movc[4] = {1, 0, -1, 0};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> R >> C) {
        board.resize(R);
        ID = 0; x2id.clear();
        Dinic din(R * C + 2);
        int s = get_id(8888);
        int t = get_id(9999);
        int tot_cap_in = 0;
        int tot_cap_out = 0;
        rep(r,0,R-1) cin >> board[r];
        rep(r,0,R-1) rep(c,0,C-1) {
            int u = get_id(r * C + c);
            int cap = 1 + (board[r][c] == '-');
            if ((r + c) % 2 == 0) {
                din.add_edge(s, u, cap);
                tot_cap_in += cap;
                rep(i,0,3) {
                    int rr = r + movr[i];
                    int cc = c + movc[i];
                    if (0 <= rr and rr < R and 0 <= cc and cc < C) {
                        int v = get_id(rr * C + cc);
                        din.add_edge(u, v, cap);
                    }
                }
            } else {
                din.add_edge(u, t, cap);
                tot_cap_out += cap;
            }
        }
        if (tot_cap_in == tot_cap_out and din.max_flow(s, t) == tot_cap_in) {
            cout << "Y\n";
        } else {
            cout << "N\n";
        }
    }
    return 0;
}