// tags: max flow, dinic
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 100;
int N;
vector<string> board;
int rows[MAXN][MAXN], cols[MAXN][MAXN];

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


int ID = 0;
map<int, int> x2id;
int get_id(int x) {
    auto it = x2id.find(x);
    if (it == x2id.end()) {
        return x2id[x] = ID++;
    }
    return it->second;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N) {
        board.resize(N);
        rep(i,0,N-1) cin >> board[i];
        ID = 0;
        set<int> row_ids, col_ids;
        rep(r,0,N-1) {
            rep(c,0,N-1) {
                if (board[r][c] == '.') {
                    rows[r][c] = ID;
                    row_ids.insert(ID);
                }
                else ++ID;                
            }
            ++ID;
        }
        rep(c,0,N-1) {
            rep(r,0,N-1) {
                if (board[r][c] == '.') {
                    cols[r][c] = ID;
                    col_ids.insert(ID);
                }
                else ++ID;                
            }
            ++ID;
        }
        Dinic din(row_ids.size() + col_ids.size() + 2);
        ID = 0; x2id.clear();
        int s = get_id(-1);
        int t = get_id(-2);
        for (int x : row_ids) {
            int u = get_id(x);
            din.add_edge(s, u, 1);
        }
        for (int x : col_ids) {
            int u = get_id(x);
            din.add_edge(u, t, 1);
        }
        rep(r,0,N-1) rep(c,0,N-1) {
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