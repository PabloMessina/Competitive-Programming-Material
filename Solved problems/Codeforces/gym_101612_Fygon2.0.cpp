// TODO: finish this
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
int char2id(char c) {
    static map<char,int> m;
    static int id = 0;
    auto it = m.find(c);
    if (it == m.end()) return m[c] = id++;
    return it->second;
}

struct tarjanSCC {
    vector<int> _stack, ids, low, scc_ids;
    vector<bool> instack;
    vector<vector<int>>* g;
    int n, ID, SCC_ID;
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
            while (1) {
                int x = _stack.back(); _stack.pop_back();
                scc_ids[x] = SCC_ID;
                instack[x] = false;
                if (x == u) break;
            }
            SCC_ID++;
        }
    }
    tarjanSCC(vector<vector<int>>& _g) {
        g = &_g;
        n = _g.size();
        _stack.reserve(n);
        ids.assign(n, -1);
        scc_ids.resize(n);
        low.resize(n);
        instack.assign(n, 0);
        ID = 0;
        SCC_ID = 0;
        rep(u, 0, n-1) if (ids[u] == -1) dfs(u);
    }
};

vector<vector<int>> g, g2;
ll memo[1 << 20];
ll dp(int mask) {
    ll& ans = memo[mask];
    // printf("dp(mask = %d), ans = %lld\n", mask, ans);
    if (ans != -1) return ans;
    if (mask == 0) return ans = 1;
    ans = 0;
    rep(u,0,g2.size()) {
        if ((mask >> u) & 1) {
            // printf("mask = %d, u = %d, g2[u].size() = %d\n", mask, u, g2[u].size());
            bool can = true;
            for (int v : g2[u]) {
                if ((mask >> v) & 1) {
                    can = false;
                    break;
                }
            }
            if (can) {
                // printf("** recursing\n");
                ans += dp(mask & ~(1 << u));
            }
        }
    }
    return ans;
}

ll fact(int n) { return n == 0 ? 1LL : n * fact(n-1); }

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int m; cin >> m;
    string tokens[5];
    rep(i,0,m-1) {
        rep(j,0,5) cin >> tokens[j];
        int a = char2id(tokens[1][0]);
        int b = char2id(tokens[3][6]);
        int c = char2id(tokens[4][0]);
        int k = max({a, b, c}) + 1;
        if (g.size() < k) g.resize(k);
        g[b].push_back(a);
        g[a].push_back(c);
    }
    tarjanSCC tscc(g);
    set<ii> scc_edges;
    rep(u,0,g.size()) {
        int uu = tscc.scc_ids[u];
        for (int v : g[u]) {
            int vv = tscc.scc_ids[v];
            if (uu != vv) scc_edges.emplace(uu, vv);
        }
    }
    g2.resize(tscc.SCC_ID);
    for (auto& e : scc_edges) {
        g2[e.ff].push_back(e.ss);
        // printf("%d -> %d\n", e.ff, e.ss);
    }
    memset(memo, -1, sizeof(ll) * (1 << g2.size()));
    ll num = dp((1 << g2.size())-1);
    ll den = fact(m-1);
    // printf("num = %lld, den = %lld\n", num, den);
    ll g = __gcd(num, den);
    num /= g, den /= g;
    cout << (m-1) << ' ' << num << '/' << den << '\n';
    return 0;
}