// tags: SCC, tarjan, graphs
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)

const int MAXN = 100000;

namespace tarjanSCC {
    const int UNVISITED = -1;
    vector<int> _stack;
    int ids[MAXN];
    int lows[MAXN];
    bool instack[MAXN];
    int ID = 0;
    vector<vector<int>>* g;

    bool dfs(int u) {
        ids[u] = lows[u] = ID++;
        instack[u] = true;
        _stack.push_back(u);
        for (int v : (*g)[u]) {
            if (ids[v] == UNVISITED) {
                if (dfs(v)) return true;
                lows[u] = min(lows[v], lows[u]);
            } else if (instack[v]) {
                lows[u] = min(lows[v], lows[u]);
            }
        }
        if (lows[u] == ids[u]) {
            vector<int> scc;
            scc.reserve(MAXN);
            while (true)  {
                int x = _stack.back(); _stack.pop_back();
                instack[x] = false;
                scc.push_back(x);
                if (x == u) break;
            }
            sort(scc.begin(), scc.end());
            cout << scc.size() << '\n';
            bool f = true;
            for (int x : scc) {
                if (f) { f = false; cout << x+1;}
                else cout << ' ' << x+1;
            }
            cout << '\n';
            return true;
        }
        return false;
    }

    void run(vector<vector<int>>& _g) {
        _stack.reserve(MAXN);
        int n = _g.size();
        g = &_g;
        memset(ids, -1, sizeof(int) * n);
        memset(instack, 0, sizeof(bool) * n);
        ID = 0;
        rep(u, 0, n-1) if (ids[u] == UNVISITED && dfs(u)) break;
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    while (m--) {
        int a, b; cin >> a >> b; a--, b--;
        g[a].push_back(b);
    }
    tarjanSCC::run(g);
    return 0;
}