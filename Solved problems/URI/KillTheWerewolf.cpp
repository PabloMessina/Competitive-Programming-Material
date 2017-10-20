// tags: max flow, Dinic
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 50
typedef long long int ll;

int indegree[MAXN];
int g[MAXN][2];

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
        edge b = {u, (int)g[u].size(), 0, cap};
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
    int n; scanf("%d", &n);
    memset(indegree, 0, sizeof indegree);
    rep(i,0,n-1) {
        int a,b; scanf("%d%d",&a,&b); --a,--b;
        g[i][0] = a, g[i][1] = b;
        indegree[a]++;
        indegree[b]++;
    }

    int count = 0;
    rep(w,0,n-1) {
        if (indegree[w] < 2) {
            count++; continue;
        }
        
        int wa = g[w][0], wb = g[w][1];
        int s = 2*n, t = 2*n+1;
        Dinic din(2*n+2);

        rep(i,0,n-1) {
            int a = g[i][0], b = g[i][1];
            if (i == w or a == w or b == w) continue;
            din.add_edge(s, i, 1);
            din.add_edge(i, n+a, 1);
            din.add_edge(i, n+b, 1);      
        }
        rep(i, 0, n-1) {
            if (i == w) continue;
            if (i == wa or i == wb)
                din.add_edge(n+i, t, indegree[w]-2);
            else
                din.add_edge(n+i, t, indegree[w]-1);
        }

        int votes = n - indegree[w] - 1;
        int mf = (int)din.max_flow(s, t);
        if (votes > mf)
            count++;
    }
    printf("%d\n", count);
    return 0;
}