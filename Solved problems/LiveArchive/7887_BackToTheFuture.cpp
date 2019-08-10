// tags: greedy, implementation, std::set, graphs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
// -------------------------------
int N, M, A, B;
vector<uset<int>> g;
set<pair<int,int>> s;

void remove_node(set<pair<int,int>>::iterator it) {
    s.erase(it);
    int u = it->second;
    for (int v : g[u]) {
        auto _it = s.find({g[v].size(), v});
        s.erase(_it);
        g[v].erase(u);
        s.emplace(g[v].size(), v);
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    g.reserve(100000);
    while (cin >> N >> M >> A >> B) {
        g.clear(); g.resize(N);
        s.clear();
        while (M--) {
            int u, v; cin >> u >> v; --u, --v;
            g[u].insert(v);
            g[v].insert(u);
        }
        rep(u,0,N-1) s.emplace(g[u].size(), u);
        bool dirty;
        do {
            dirty = false;
            while (!s.empty() and s.begin()->first < A) {
                remove_node(s.begin());
                dirty = true;
            }
            while (!s.empty() and (s.size() - s.rbegin()->first - 1) < B) {
                remove_node(prev(s.end()));
                dirty = true;
            }
        } while (dirty);
        cout << s.size() << '\n';
    }
    return 0;
}