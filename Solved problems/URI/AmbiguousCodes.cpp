// tags: dijkstra, graphs, implementation
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
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int N;
map<pair<string,int>, int> si2id;
int ID = 0;
int get_id(const string& s, int i) {
    auto k = make_pair(s, i);
    auto it = si2id.find(k);
    if (it == si2id.end()) return si2id[k] = ID++;
    return it->ss;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    while (cin >> N and N) {
        vector<string> words(N);
        for (string& w : words) cin >> w;
        
        // build graph
        vector<vector<ii>> g;
        si2id.clear(); ID = 0;
        queue<pair<string, int>> q;
        q.emplace("", 0);
        uset<int> vis;
        vis.insert(0);
        while (!q.empty()) {
            string s; int b; tie(s, b) = q.front(); q.pop();
            int n = s.size();
            int u = get_id(s, b);
            if (g.size() <= u) g.resize(u+1);
            for (string& w : words) {
                int m = w.size();
                if (strncmp(s.c_str(), w.c_str(), min(n,m)) == 0) {
                    if (n == m and b) {
                        int v = get_id("", 1);                        
                        g[u].emplace_back(v, 0);
                    }
                    if (n != m) {
                        string ss = n < m ? w.substr(n) : s.substr(m);
                        int bb = u != 0;
                        int v = get_id(ss, bb);
                        g[u].emplace_back(v, n > m ? 0 : m - n);
                        if (vis.count(v) == 0) {
                            q.emplace(ss, bb);
                            vis.insert(v);
                        }
                    }
                }
            }
        }
        g.resize(ID);

        // dijkstra
        priority_queue<ii, vector<ii>, greater<ii>> pq;
        vector<int> D(g.size(), INT_MAX);
        D[0] = 0;
        pq.emplace(0, 0);
        while (!pq.empty()) {
            int w, u; tie(w, u) = pq.top(); pq.pop();
            if (D[u] < w) continue;
            for (auto& e : g[u]) {
                if (D[e.ff] > w + e.ss) {
                    D[e.ff] = w + e.ss;
                    pq.emplace(w + e.ss, e.ff);
                }
            }
        }

        // output
        int ans_id = get_id("", 1);
        int ans = ans_id == D.size() ? INT_MAX : D[ans_id];
        if (ans == INT_MAX) ans = -1;
        cout << ans << '\n';
    }
    return 0;
}