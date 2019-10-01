// tags: max flow, dijkstra, binary search, bitwise, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
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

int N, M, S;
vector<ll> P;
vector<vector<pair<int, ll>>> g;
vector<int> si;
vector<ll> sc;
vector<ll> mintime[10];

void calc_mintime(int s, int idx) {
    vector<ll>& T = mintime[idx];
    T.assign(N, LLONG_MAX);
    priority_queue<pair<ll,int>, vector<pair<ll,int>>,
                greater<pair<ll,int>>> pq;
    T[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto p = pq.top(); pq.pop();
        ll t; int u; tie(t, u) = p;
        if (T[u] < t) continue;
        for (auto& e : g[u]) {
            int v; ll w; tie(v,w) = e;
            if (T[v] > t + w) {
                T[v] = t + w;
                pq.emplace(t + w, v);
            }
        }
    }
}

ll tot_people;

bool possible(ll t) {
    static ll X[1 << 10];
    int n = 1 << S;
    fill(X, X+n, 0);
    rep(i,0,N-1) {
        int mask = 0;
        rep(j,0,S-1) {
            if (mintime[j][i] <= t) mask |= 1 << j;
        }
        X[mask] += P[i];
    }
    Dinic din(n + S + 2);
    int src = n + S;
    int dst = src + 1;
    rep(mask,0,n-1) {
        din.add_edge(src, mask, X[mask]);
        for (int j = 0, b=mask; b; b >>=1, j++) {
            if (b & 1) {
                din.add_edge(mask, n + j, sc[j]);
            }
        }
    }
    rep(i, 0, S-1) din.add_edge(n+i, dst, sc[i]);
    return din.max_flow(src, dst) == tot_people;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> S;
    P.resize(N);
    tot_people = 0;
    rep(i,0,N-1) {
        cin >> P[i]; tot_people += P[i];
    }
    g.resize(N);
    while (M--) {
        int u, v; ll w;
        cin >> u >> v >> w; --u, --v;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    si.resize(S); sc.resize(S);    
    rep(i,0,S-1) {
        cin >> si[i] >> sc[i];
        si[i]--;
        calc_mintime(si[i], i);
    }
    ll l = 0, r = (ll)1e15;
    while (l < r) {
        ll m = (l+r) >> 1;
        if (possible(m)) r = m;
        else l = m+1;
    }
    cout << l << '\n';
    return 0;
}