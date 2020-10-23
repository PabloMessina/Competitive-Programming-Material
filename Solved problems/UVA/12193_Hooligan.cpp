// tags: max flow, Dinic
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------

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
        int s = get_id(888888), t = get_id(999999);
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