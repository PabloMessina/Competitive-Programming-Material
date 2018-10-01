// tags: bipartite matching, maxflow, dinic
#include <bits/stdc++.h> // import everything in one shot
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

const int MAXR = 20;
int R,C,N;
char board[MAXR][MAXR+1];

namespace ID_MAPPER {
    umap<int,int> x2id;
    int ID;
    void reset() {
        x2id.clear();
        ID = 0;
    }
    int get_id(int x) {
        auto it = x2id.find(x);
        if (it == x2id.end()) return x2id[x] = ID++;
        return it->second;
    }
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

const int dirs[4][2] = {{0,1},{0,-1},{1,0},{-1,0}};

int main() {
    main_loop:
    while (scanf("%d%d", &R, &C) == 2) {
        int even_count = 0;
        int odd_count = 0;
        rep(r,0,R-1) {
            scanf("%s", board[r]);
            rep(c,0,C-1) {
                if (board[r][c] == 'o') {
                    if ((r+c)%2==0) even_count++;
                    else odd_count++;
                } else {
                    if ((r+c)%2==0) even_count+=2;
                    else odd_count+=2;
                }
            }
        }
        if (even_count != odd_count) {
            puts("N");
            goto main_loop;
        }
        N = even_count + odd_count + 2;
        ID_MAPPER::reset();
        int source = ID_MAPPER::get_id(88888);
        int target = ID_MAPPER::get_id(99999);
        Dinic din(N);
        rep(r,0,R-1) {
            rep(c,0,C-1) {
                if (board[r][c] == 'o') {
                    int u = ID_MAPPER::get_id(r * C + c);
                    if ((r+c) % 2 == 0) {
                        din.add_edge(source, u, 1);
                        rep(i,0,3) {
                            int rr = r + dirs[i][0];
                            int cc = c + dirs[i][1];
                            if (0 <= rr and rr < R and 0 <= cc and cc < C) {
                                if (board[rr][cc] == 'o') {
                                    int v = ID_MAPPER::get_id(C * rr + cc);
                                    din.add_edge(u, v, 1);
                                } else {
                                    int v1 = ID_MAPPER::get_id(C * rr + cc);
                                    int v2 = ID_MAPPER::get_id(R*C + C * rr + cc);
                                    din.add_edge(u, v1, 1);
                                    din.add_edge(u, v2, 1);
                                }
                            }
                        }
                    } else {
                        din.add_edge(u, target, 1);
                    }                    
                } else {
                    int u1 = ID_MAPPER::get_id(r * C + c);
                    int u2 = ID_MAPPER::get_id(R*C + r * C + c);
                    if ((r+c) % 2 == 0) {
                        din.add_edge(source, u1, 1);
                        din.add_edge(source, u2, 1);
                        rep(i,0,3) {
                            int rr = r + dirs[i][0];
                            int cc = c + dirs[i][1];
                            if (0 <= rr and rr < R and 0 <= cc and cc < C) {
                                if (board[rr][cc] == 'o') {
                                    int v = ID_MAPPER::get_id(C * rr + cc);
                                    din.add_edge(u1, v, 1);
                                    din.add_edge(u2, v, 1);
                                } else {
                                    int v1 = ID_MAPPER::get_id(C * rr + cc);
                                    int v2 = ID_MAPPER::get_id(R*C + C * rr + cc);
                                    din.add_edge(u1, v1, 1);
                                    din.add_edge(u1, v2, 1);
                                    din.add_edge(u2, v1, 1);
                                    din.add_edge(u2, v2, 1);
                                }
                            }
                        }
                    } else {
                        din.add_edge(u1, target, 1);
                        din.add_edge(u2, target, 1);
                    }                    
                }
            }
        }
        if (din.max_flow(source, target) == even_count)
            puts("Y");
        else
            puts("N");
    }
    return 0;
}