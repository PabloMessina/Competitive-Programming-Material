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
mt19937 rng(114514);
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, p;
    cin >> n >> m >> p;
    vector<string> c(n);
    rep(i,0,n) cin >> c[i];
    int max_size = 0;
    vector<char> ans(m, '0');
    rep(_,0,20) {
        int x = rng() % n;
        vector<int> idxs;
        rep(i,0,m) if (c[x][i] == '1') idxs.push_back(i);
        p = idxs.size();
        vector<int> f(1 << p, 0);
        rep(i,0,n) {
            int mask = 0;
            rep(j,0,p) if (c[i][idxs[j]] == '1') mask |= (1 << j);
            f[mask]++;
        }
        rep(i,0,p) rep(s,0,1<<p) if (!(s & (1 << i))) {
            f[s] += f[s | (1 << i)];
        }
        rep(s, 1, 1 << p) {
            if (f[s] * 2 < n) continue;
            int n_ones = __builtin_popcount(s);
            if (n_ones <= max_size) continue;
            max_size = n_ones;
            rep (i,0,m) ans[i] = '0';
            rep (i,0,p) if (s & (1 << i)) ans[idxs[i]] = '1';
        }
    }
    for (char c : ans) cout << c;
    cout << '\n';
    return 0;
}