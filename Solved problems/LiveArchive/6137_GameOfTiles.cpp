// tags: bipartite matching, max-flow, dinic
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------

int R,C;
string board[50];

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

int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

namespace ID_MAPPER {
    umap<int,int> x2id;
    int ID = 0;
    void reset() {
        x2id.reserve(10000);
        x2id.clear();
        ID = 0;
    }
    int get_id(int x) {
        auto ret = x2id.emplace(x, ID);
        if (ret.second) ID++;
        return ret.first->second;
    }
}

int inline get_hash(int i, int j) { return i * C + j; } 

int main() {
    while (cin >> R >> C) {
        int nw = 0, nb = 0;
        rep(i,0,R-1){
            cin >> board[i];
            rep(j,0,C-1) {
                if (board[i][j] == '.') {
                    if ((i+j)%2) nw++;
                    else nb++;
                }
            }
        }
        if (nw != nb) {
            cout << "1\n";
            continue;
        }
        ID_MAPPER::reset();
        Dinic din(nw + nb + 2);
        int s = ID_MAPPER::get_id(8888);
        int t = ID_MAPPER::get_id(9999);
        rep(i,0,R-1) rep(j,0,C-1) if (board[i][j] == '.') {
            int u = ID_MAPPER::get_id(get_hash(i,j));
            if ((i+j)%2) {
                din.add_edge(s,u,1);
                rep(k,0,3) {
                    int ii = i + dirs[k][0];
                    int jj = j + dirs[k][1];                
                    if (0 <= ii and ii < R and 0 <= jj and jj < C and
                            board[ii][jj] == '.') {
                        int v = ID_MAPPER::get_id(get_hash(ii,jj));
                        din.add_edge(u,v,1);
                    }
                }
            } else {
                din.add_edge(u,t,1);
            }
        }
        if (din.max_flow(s,t) == nb) {
            cout << "2\n";
        } else {
            cout << "1\n";
        }
    }    
    return 0;
}