// tags: graphs, implementaton, greedy
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
vector<uset<int>> g;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;    
    while (t--) {
        int n, k; cin >> n >> k;
        g.assign(n, uset<int>());
        rep(i,1,n) {
            int x, y; cin >> x >> y; --x, --y;
            g[x].insert(y);
            g[y].insert(x);
        }
        vector<int> leaves(n, 0);
        rep(i,0,n) {
            if (g[i].size() == 1) {
                leaves[*g[i].begin()]++;
            }
        }
        priority_queue<pair<int,int>> q;
        rep(i,0,n) {
            if (leaves[i] > 0) {
                q.emplace(leaves[i], i);
            }
        }
        int moves = 0;
        while (q.size()) {
            int l, u; tie(l,u) = q.top(); q.pop();
            if (l != leaves[u]) continue;
            if (l < k) break;
            int u_moves = l/k;
            moves += u_moves;
            vector<int> to_erase;
            for (int v : g[u]) {
                if (g[v].size() == 1) {
                    to_erase.push_back(v);
                }
            }
            assert (to_erase.size() == l);
            rep(i,0,u_moves*k) {
                g[u].erase(to_erase[i]);
                leaves[u]--;
                g[to_erase[i]].erase(u);
                leaves[to_erase[i]] = 0;
            }
            if (g[u].size() == 1) {
                int p = *g[u].begin();
                leaves[p]++;
                q.emplace(leaves[p], p);
            }
        }
        cout << moves << '\n';
    }
    return 0;
}