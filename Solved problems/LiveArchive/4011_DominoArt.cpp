// tags: bicoloration, maximum bipartite matching
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
int board[MAXR][MAXR];
int dirs[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
enum { BLACK, WHITE, SHARP, DOT };
char buff[MAXR + 1];

int main() {
    int _case = 1;
    mainloop:
    while (true) {

        // read board
        scanf("%d%d", &R, &C);
        if (R == 0 && C == 0) break;
        rep(r,0,R-1) {
            scanf("%s", buff);
            rep(c,0,C-1) {
                board[r][c] = (buff[c] == '#') ? SHARP : DOT;
            }
        }

        int counts[2] = {0, 0}; // black and white counters

        // --- bicoloration of connected components with BFS        
        rep(r,0,R-1) rep(c,0,C-1) {            
            if (board[r][c] == SHARP) {
                queue<ii> q;                
                board[r][c] = WHITE;
                counts[WHITE]++;
                q.emplace(r,c);

                while (!q.empty()) {
                    ii curr = q.front(); q.pop();

                    int ucolor = board[curr.first][curr.second];
                    int vcolor = 1 - ucolor;
                    int uid = curr.first * C + curr.second;
                    
                    rep(i,0,3) {
                        int rr = curr.first + dirs[i][0];
                        int cc = curr.second + dirs[i][1];
                        if (0 <= rr and rr < R and 0 <= cc and cc < C
                            and board[rr][cc] == SHARP)
                        {
                            int vid = rr * C + cc;
                            q.emplace(rr, cc);
                            board[rr][cc] = vcolor;
                            counts[vcolor]++;
                        }
                    }
                }

                // check same number of white and black cells
                if (counts[WHITE] != counts[BLACK]) {
                    printf("Case %d: Impossible\n", _case++);
                    goto mainloop;
                }
            }
        }

        // ----- DINIC (maximum bipartite matching) -----

        int n = counts[WHITE] + counts[BLACK];
        Dinic din(n+2);
        int sid = n;
        int tid = n+1;

        // map indexes to ids
        umap<int,int> idx2id;
        int id = 0;
        rep(r,0,R-1) rep(c,0,C-1) {
            if (board[r][c] != DOT)  idx2id[r * C + c] = id++;
        }

        // build graph
        rep(r,0,R-1) rep(c,0,C-1) {            
            int color = board[r][c];
            if (color == DOT) continue;
            int uid = idx2id[r * C + c];
            if (color == WHITE) {
                din.add_edge(sid, uid, 1);
                rep(i,0,3) {
                    int rr = r + dirs[i][0];
                    int cc = c + dirs[i][1];
                    if (0 <= rr and rr < R and 0 <= cc and cc < C and board[rr][cc] == BLACK) {
                        int vid = idx2id[rr * C + cc];
                        din.add_edge(uid, vid, 1);
                    }
                }
            } else {
                din.add_edge(uid, tid, 1);
            }
        }

        // find max flow and print answer
        if (din.max_flow(sid, tid) == counts[WHITE]) {
            printf("Case %d: Possible\n", _case);
        } else {
            printf("Case %d: Impossible\n", _case);
        }
        _case++;
    }
    return 0;
}