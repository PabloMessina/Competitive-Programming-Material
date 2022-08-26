// tags: SCC, tarjan, DAGs, top-down DP, graphs
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
typedef pair<int,int> ii;
// -------------------------------

const int MAXN = 1000000;
int N,M,S,E;
ll funs[MAXN];
vector<vector<int>> g;
int SCC_ID = 0;
int scc_ids[MAXN];

vector<vector<int>> dag;
int dagS, dagE;
ll dag_funs[MAXN] = {0};
set<ii> dag_edges;

ll memo[MAXN];
ll dp(int u) {
    ll& ans = memo[u];
    if (ans != -1) return ans;
    if (u == dagE) return ans = dag_funs[dagE];
    ll tmp = LLONG_MIN;
    for (int v : dag[u]) tmp = max(tmp, dp(v));
    if (tmp != LLONG_MIN) tmp += dag_funs[u];
    return ans = tmp;
}

namespace tarjanSCC {
    const int UNVISITED = -1;
    vector<int> _stack;
    int ids[MAXN]; // ids[u] = id assigned to node u
    int lows[MAXN]; // lows[u] = lowest id reachable by node u
    bool instack[MAXN]; // instack[u] = if u is currently in stack or not
    int ID = 0; // global variable used to assign ids to unvisited nodes
    vector<vector<int>>* g; // pointer to graph

    void dfs(int u) {
        ids[u] = lows[u] = ID++; // assign ID to new visited node
        // add to stack
        instack[u] = true;
        _stack.push_back(u);
        // check neighbor nodes
        for (int v : (*g)[u]) {
            if (ids[v] == UNVISITED) { // if unvisited -> visit 
                dfs(v);
                lows[u] = min(lows[v], lows[u]); // update u's low
            } else if (instack[v]) { // visited AND in stack
                lows[u] = min(lows[v], lows[u]); // update u's low
            }
        }
        if (lows[u] == ids[u]) { // u is the root of a SCC
            // remove SCC from top of the stack
            while (true)  {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                scc_ids[x] = SCC_ID;
                dag_funs[SCC_ID] += funs[x];
                if (x == u) break;
            }
            SCC_ID++;
        }
    }

    void run(vector<vector<int>>& _g) {
        _stack.reserve(MAXN); // reserve enough space to avoid memory reallocations
        int n = _g.size(); // number of nodes
        g = &_g; // pointer to graph
        // reset variables
        memset(ids, -1, sizeof(int) * n);
        memset(instack, 0, sizeof(bool) * n);
        ID = 0;
        // run dfs's
        rep(u, 0, n-1) if (ids[u] == UNVISITED) dfs(u);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M >> S >> E;
    --S, --E;
    rep(i,0,N) cin >> funs[i];
    g.assign(N, vector<int>());
    while (M--) {
        int a, b; cin >> a >> b; --a, --b;
        g[a].push_back(b);
    }
    tarjanSCC::run(g);
    rep(u,0,N) {
        for (int v : g[u]) {
            if (scc_ids[u] != scc_ids[v])
                dag_edges.emplace(scc_ids[u], scc_ids[v]);
        }
    }
    dag.resize(SCC_ID);
    for (auto& p : dag_edges) dag[p.first].push_back(p.second);
    memset(memo, -1, sizeof(memo[0]) * SCC_ID);
    dagS = scc_ids[S];
    dagE = scc_ids[E];
    cout << dp(dagS) << '\n';
    return 0;
}