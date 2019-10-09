// tags: SCC, tarjan, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
using namespace std;
//----------------------
ll MOD = 1000000007;
ll min_totcost;
ll ways;
ll costs[100000];

struct tarjanSCC {
    vector<int> _stack, ids, low;
    vector<bool> instack;
    vector<vector<int>>* g;
    int ID;
    void dfs(int u) {
        ids[u] = low[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (int v : (*g)[u]) {
            if (ids[v] == -1) {
                dfs(v);
                low[u] = min(low[v], low[u]);
            } else if (instack[v]) {
                low[u] = min(low[v], low[u]);
            }
        }
        if (low[u] == ids[u]) {
            ll mincost = LLONG_MAX;
            ll count = 0;
            while (1) {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                if (mincost == costs[x]) count++;
                else if (mincost > costs[x]) mincost = costs[x], count = 1;
                if (x == u) break;
            }
            min_totcost += mincost;
            ways = (ways * count) % MOD;
        }
    }
    tarjanSCC(vector<vector<int>>& _g) {
        g = &_g;
        int n = _g.size();
        _stack.reserve(n);
        ids.assign(n, -1);
        low.resize(n);
        instack.assign(n, 0);
        ID = 0;
        rep(u, 0, n-1) if (ids[u] == -1) dfs(u);
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int N, M;
    cin >> N;
    rep(i,0,N-1) cin >> costs[i];
    cin >> M;
    vector<vector<int>> g(N);
    rep(i,1,M) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }
    min_totcost = 0;
    ways = 1;
    tarjanSCC tscc(g);
    cout << min_totcost << " " << ways << '\n';
    return 0;
}