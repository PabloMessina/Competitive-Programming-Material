// tags: SCC, tarjan, graphs
#include <bits/stdc++.h>
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
using namespace std;

const int MAXN = 100000;
int N, M;
ll costs[MAXN];
vector<int> g[MAXN];

ll MOD = 1000000007;
ll min_totcost;
ll ways;

const int UNVISITED = -1;
vector<int> _stack;
int ids[MAXN];
int lows[MAXN];
bool instack[MAXN];
int ID = 0;
void dfs(int u) {
    ids[u] = lows[u] = ID++;
    instack[u] = true;
    _stack.push_back(u);
    for (int v : g[u]) {
        if (ids[v] == UNVISITED) {
            dfs(v);
            lows[u] = min(lows[v], lows[u]);
        } else if (instack[v]) {
            lows[u] = min(lows[v], lows[u]);
        }
    }
    if (lows[u] == ids[u]) {
        ll mincost = LLONG_MAX;
        int i = _stack.size() - 1;
        while (true)  {
            mincost = min(mincost, costs[_stack[i]]);
            instack[_stack[i]] = false;
            if (_stack[i] == u) break;
            i--;
        }
        int freq = 0;
        rep(j,i,_stack.size()-1) if (costs[_stack[j]] == mincost) freq++;
        min_totcost += mincost;
        ways = (ways * freq) % MOD;
        _stack.resize(i);
    }
}
void tarjanSCC() {
    memset(ids, -1, sizeof(int) * N);
    memset(instack, 0, sizeof(bool) * N);
    ID = 0;
    _stack.reserve(N);
    rep(u, 0, N-1) {
        if (ids[u] == UNVISITED) {
            dfs(u);
        }
    }
}

int main() {
    cin >> N;
    rep(i,0,N-1) cin >> costs[i];
    cin >> M;
    rep(i,1,M) {
        int u, v; cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
    }
    min_totcost = 0;
    ways = 1;
    tarjanSCC();
    cout << min_totcost << " " << ways << '\n';
    return 0;
}