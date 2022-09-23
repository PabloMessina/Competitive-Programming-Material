// tags: LCA, jump pointers, minimum spanning tree, Prim / Kruskal
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
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

const int MAXN = 200000;
int N;
vector<ii> g[MAXN], mst[MAXN];

namespace Prim { // minimun spanning tree
    struct Edge {
        int u, v, cost;
        bool operator<(const Edge& o) const {
            return cost > o.cost;
        }
    };
    bool visited[MAXN] = {0};
    ll find_mst() {
        ll total_cost = 0;
        priority_queue<Edge> q;
        visited[0] = true;
        for (ii& p : g[0]) q.push({0, p.first, p.second});
        int count = 1;
        while (!q.empty()) {
            Edge edge = q.top(); q.pop();
            if (visited[edge.v]) continue;
            int u = edge.u;
            int v = edge.v;
            int cost = edge.cost;
            visited[v] = true;
            total_cost += cost;
            mst[u].emplace_back(v, cost);
            mst[v].emplace_back(u, cost);
            if (++count == N) break;
            for (ii p : g[v]) {
                if (visited[p.first]) continue;
                q.push({v, p.first, p.second});                
            }            
        }
        return total_cost;
    }
}

namespace LCA { // lowest common ancestor, binary lifting (power of 2 jumps) method.
// The code is modified to remember the maximum cost edge from each node
// to each of its power of 2 ancestors
    const int MAXLOG = 31 - __builtin_clz(MAXN);
    int P[MAXN][MAXLOG+1];
    int maxcost[MAXN][MAXLOG+1];
    int D[MAXN];

    inline int log2(int x) { return 31 - __builtin_clz(x); }

    void dfs(int u, int p, int d, int cost) {
        P[u][0] = p;
        maxcost[u][0] = cost;
        D[u] = d;
        for (ii& e : mst[u]) {
            if (D[e.first] == -1) {
                dfs(e.first, u, d+1, e.second);
            }
        }
    }

    void init() {
        memset(D, -1, sizeof(int) * N);
        dfs(0, -1, 0, -1);
        rep(j,1,MAXLOG+1) {
            rep(i,0,N) {
                int p = P[i][j-1];
                if (p == -1) {
                    P[i][j] = -1;
                    maxcost[i][j] = -1;
                } else {
                    P[i][j] = P[p][j-1];
                    if (P[i][j] == -1) {
                        maxcost[i][j] = -1;
                    } else {
                        maxcost[i][j] = max(maxcost[i][j-1], maxcost[p][j-1]);
                    }                    
                }
            }
        }
    }

    int find_path_maxcost(int u, int v) {
    // similar to LCA(u,v) but modified to return the maximum cost edge
    // in the path u -> LCA(u,v) -> v
        if (D[u] < D[v]) swap(u, v);        
        int maxc = 0;
        int diff = D[u] - D[v];
        while (diff) {
            int j = log2(diff);
            maxc = max(maxc, maxcost[u][j]);
            u = P[u][j];
            diff -= (1 << j);
        }
        if (u == v) return maxc;
        invrep (j, MAXLOG, 0) {
            if (P[u][j] != P[v][j]) {
                maxc = max(maxc, maxcost[u][j]);
                maxc = max(maxc, maxcost[v][j]);
                u = P[u][j], v = P[v][j];
            }
        }
        maxc = max(maxc, maxcost[u][0]);
        maxc = max(maxc, maxcost[v][0]);
        return maxc;
    }
}

int main() {
    // read and build graph
    int m;
    scanf("%d%d", &N, &m);
    vector<iii> edges;
    edges.reserve(m);
    while (m--) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        --a, --b;
        g[a].emplace_back(b, c);
        g[b].emplace_back(a, c);
        edges.emplace_back(a, b, c);
    }
    // build minimum spanning tree and get its total cost
    ll mstcost = Prim::find_mst();
    // init LCA sparse tables
    LCA::init();
    // print answer for each edge
    for (auto& e : edges) {
        int u, v, edgecost;
        tie(u, v, edgecost) = e;
        int pathmax = LCA::find_path_maxcost(u, v);
        printf("%lld\n", mstcost + edgecost - pathmax);
    }
    return 0;
}