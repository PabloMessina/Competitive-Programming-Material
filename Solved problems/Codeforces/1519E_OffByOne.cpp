// tags: implementation, dfs, graphs, greedy
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
struct Frac {
    ll a, b;
    normalize() {
        ll g = __gcd(a, b);
        a /= g;
        b /= g;
    }
    Frac operator+(ll x) const {
        Frac ans = {a + b * x, b};
        ans.normalize();
        return ans;
    }
    Frac operator/(Frac o) const {
        Frac ans = {a * o.b, b * o.a};
        ans.normalize();
        return ans;
    }
    bool operator<(const Frac& o) const {
        return a * o.b < b * o.a;
    }
};
int ID = 0;
map<Frac,int> m2id;
int get_id(Frac& m) {
    auto it = m2id.find(m);
    if (it == m2id.end()) return m2id[m] = ID++;
    return it->second;
}
vector<vector<ii>> g;
vector<ii> moves;
vector<int> D;
int dfs(int u, int p, int d) {
    D[u] = d;
    int ans = -1;
    for (auto& x : g[u]) {
        int v, i; tie(v,i) = x;
        if (v == p) continue;
        if (D[v] == -1) {
            int j = dfs(v, u, d+1);
            if (j != -1) {
                moves.emplace_back(i, j);
            } else if (ans != -1) {
                moves.emplace_back(i, ans);
                ans = -1;
            } else {
                ans = i;
            }
        } else if (D[v] > D[u]) {
            if (ans != -1) {
                moves.emplace_back(i, ans);
                ans = -1;
            } else {
                ans = i;                
            }
        }
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    rep(i,0,n) {
        Frac x1, y1;
        cin >> x1.a >> x1.b >> y1.a >> y1.b;
        x1.normalize();
        y1.normalize();
        Frac x2 = x1 + 1;
        Frac y2 = y1 + 1;
        Frac m1 = y1/x2;
        Frac m2 = y2/x1;
        int u1 = get_id(m1);
        int u2 = get_id(m2);
        if (u1 >= g.size()) g.resize(u1+1);
        if (u2 >= g.size()) g.resize(u2+1);
        g[u1].emplace_back(u2, i);
        g[u2].emplace_back(u1, i);
    }
    D.assign(g.size(), -1);    
    rep(u,0,g.size()) if (D[u] == -1) dfs(u, -1, 0);
    cout << moves.size() << '\n';
    for (auto& m : moves) {
        cout << (m.ff + 1) << ' ' << (m.ss + 1) << '\n';
    }
    return 0;
}