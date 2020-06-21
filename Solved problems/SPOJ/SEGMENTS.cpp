// tags: math, inequalities, graphs, bellman ford, shortest path, negative cycle,
// implementation, binary search
// references:
// https://codeforces.com/blog/entry/58621
// https://www.cse.huji.ac.il/course/2002/dast/slides/BellmanFord.pdf
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
bool bellmanford(vector<vector<ii>>& g, int s) {
    int n = g.size();
    vector<int> d(n, INT_MAX);
    d[s] = 0;
    rep(_,1,n) rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
        d[e.ff] = min(d[e.ff], d[u] + e.ss);
    }
    rep(u,0,n) if (d[u] < INT_MAX) for (auto& e : g[u]) {
        if (d[e.ff] > d[u] + e.ss) return true;
    }
    return false;
}
bool possible(vector<pair<ll,ll>>& segs, int n, int r) {
    vector<vector<ii>> g(n+1);
    for (auto& p : segs) {
        int u, v; tie(u,v) = p;
        g[u].emplace_back(v, r);
        g[v].emplace_back(u, -1);
    }
    rep(u,1,n) g[u].emplace_back(u-1, 0);
    int s = n;
    rep(u,0,n) g[s].emplace_back(u, 0);
    return not bellmanford(g, s);
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int N; cin >> N;
    vector<pair<ll,ll>> segs;
    set<ll> xset;
    rep(i,0,N) {
        ll a, b, h; cin >> a >> b >> h;
        a = 1000 * a + 1;
        b = 1000 * b - 1;
        segs.emplace_back(a, b);
        xset.insert(a);
        xset.insert(b);
    }
    umap<ll,int> x2id;
    int id = 0;
    for (ll x : xset) x2id[x] = id++;
    for (auto& p : segs) {
        p.ff = x2id[p.ff];
        p.ss = x2id[p.ss];
    }
    int l = 1, r = N;
    while (l < r) {
        int m = (l+r)>>1;
        if (possible(segs, id, m)) r = m;
        else l = m+1;
    }
    cout << l << '\n';
    return 0;
}