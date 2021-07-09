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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
struct AC {
    int c = 0, ec = 0, M, A;
    vector<vi> N, G; vi L, E;
    AC (int M, int A) : M(M), A(A), N(M, vi(A, 0)), E(M, 0) {}
    int add(string s) {
        int p = 0;
        for (char l : s) {
            int t = l - 'a';
            if (!N[p][t]) N[p][t] = ++c;
            p = N[p][t];
        } E[p]++;
        return p;
    }
    void init() {
        L.assign(M, 0), G.assign(M, {});
        queue<int> q; q.push(0); L[0] = -1;
        while (!q.empty()) {
            int p = q.front(); q.pop();
            rep(c, 0, A) {
                int u = N[p][c]; if (!u) continue;
                L[u] = L[p] == -1 ? 0 : N[L[p]][c], q.push(u);
                G[L[u]].pb(u);
            }
            if (p) rep(c, 0, A) if (!N[p][c]) N[p][c] = N[L[p]][c];
        }
    }
};
struct FT {
    vector<int> t;
    FT(int n) { t.assign(n+1, 0); }    
    int query(int i) {
        int ans = 0;
        for (; i; i -= (i & -i)) ans += t[i];
        return ans;
    }    
    int query(int i, int j) { return query(j) - query(i-1); }
    void update(int i, int v) {
        for (; i < t.size(); i += i & (-i)) t[i] += v;
    }
};
const int MAXN = 1e6 + 10;
int N, K;
vector<string> names;
vector<int> L, R, nodes;
int idx;
void euler_tour(int u, AC& ac, FT& ft) {    
    for (int v : ac.G[u]) {
        L[v] = idx; ft.update(idx++, ac.E[v]);
        euler_tour(v, ac, ft);
        R[v] = idx; ft.update(idx++, -ac.E[v]);
    }
}
vector<bool> active;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> K;
    AC ac(MAXN, 26);
    names.resize(K), nodes.resize(K), active.assign(K, true);
    rep(i,0,K) { cin >> names[i]; nodes[i] = ac.add(names[i]); }
    ac.init();
    FT ft(2 * MAXN);
    L.resize(2 * MAXN), R.resize(2 * MAXN);
    idx = 1; euler_tour(0, ac, ft);
    while (N--) {
        char q; cin >> q;
        if (q == '?') {
            string s; cin >> s;
            int u = 0, ans = 0;
            for (char c : s) {
                u = ac.N[u][c-'a'];
                ans += ft.query(L[u]);
            }
            cout << ans << '\n';
        } else if (q == '+') {
            int i; cin >> i; --i;
            if (!active[i]) {
                int u = nodes[i];
                ft.update(L[u], 1); ft.update(R[u], -1);
                active[i] = true;
            }
        } else {
            int i; cin >> i; --i;
            if (active[i]) {
                int u = nodes[i];
                ft.update(L[u], -1); ft.update(R[u], 1);
                active[i] = false;
            }
        }
    }
    return 0;
}