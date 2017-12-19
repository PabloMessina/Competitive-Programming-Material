// tags: max flow, dinic
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100;
char board[MAXN][MAXN+1];
int rows[MAXN][MAXN];
int cols[MAXN][MAXN];


class Dinic {
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
 
public:
    Dinic(int n) {
        this->n = n;
        g.resize(n);
        dist.resize(n);
        q.resize(n);
    }
 
    void add_edge(int u, int v, ll cap) {
        edge a = {v, (int)g[v].size(), 0, cap};
        edge b = {u, (int)g[u].size(), 0, 0};
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

int main() {
    int N;
    while (scanf("%d", &N) == 1) {
        rep(i,0,N-1) scanf("%s", board[i]);
        int r = -1;
        bool out;
        // rows
        rep(i,0,N-1) {
            out = true;
            rep(j,0,N-1) {
                if (board[i][j] == '.') {
                    if (out) { ++r; out = false; }
                    rows[i][j] = r;
                } else {
                    rows[i][j] = -1;
                    out = true;
                }
            }
        }
        // cols
        int c = -1;
        rep(j,0,N-1) {
            out = true;
            rep(i,0,N-1) {
                if (board[i][j] == '.') {
                    if (out) { ++c; out = false; }
                    cols[i][j] = c;
                } else {
                    cols[i][j] = -1;
                    out = true;
                }
            }
        }
        // --
        int NR = r+1;
        int NC = c+1;
        int s = 0, t = NR+NC+1;
        Dinic din(NR+NC+2);
        rep(r,0,NR-1) din.add_edge(s,1+r,1);
        rep(c,0,NC-1) din.add_edge(1+NR+c,t,1);
        rep(i,0,N-1) {
            rep(j,0,N-1) {
                int r = rows[i][j];
                int c = cols[i][j];
                if (r >= 0) {
                    din.add_edge(1+r,1+NR+c,1);
                }
            }
        }
        printf("%lld\n", din.max_flow(s,t));
    }
    return 0;
}