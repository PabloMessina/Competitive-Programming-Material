// tags: maximum bipartite matching, max flow, Dinic
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
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

// --- Dinic struct for max flow
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

const int MAXR = 60;
int R, C;
char board[MAXR][MAXR+1];
int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

int main() {
    int _case = 1;
    mainloop:
    while (true) {
        scanf("%d%d", &R, &C);
        if (R == 0 && C == 0) break;        
        
        int counts[2] = {0, 0};
        umap<int,int> idx2id;
        int id = 0;
        rep(r,0,R-1) {
            scanf("%s", board[r]);
            rep(c,0,C-1) if (board[r][c] == '#') {
                counts[(r + c)&1]++; // count colors
                idx2id[r * C + c] = id++; // map positions to ids
            }
        }

        // check same name number of white and black cells
        if (counts[0] != counts[1]) {
            printf("Case %d: Impossible\n", _case++);
            goto mainloop;
        }
        
        // --- maximum bipartite matching ---
        Dinic din(id+2);
        int sid = id;
        int tid = id+1;
        rep(r,0,R-1) rep(c,0,C-1) if (board[r][c] == '#') {
            int uid = idx2id[r * C + c];
            if ((r+c)&1) {
                din.add_edge(sid, uid, 1);
                rep(i,0,3) {
                    int rr = r + dirs[i][0];
                    int cc = c + dirs[i][1];
                    if (0 <= rr and rr < R and 0 <= cc and cc < C and board[rr][cc] == '#') {
                        int vid = idx2id[rr * C + cc];
                        din.add_edge(uid, vid, 1);
                    }
                }
            } else {
                din.add_edge(uid, tid, 1);
            }
        }

        // find max flow and print answer
        if (din.max_flow(sid, tid) == counts[0]) {
            printf("Case %d: Possible\n", _case);
        } else {
            printf("Case %d: Impossible\n", _case);
        }
        _case++;
    }
    return 0;
}