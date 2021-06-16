// tags: two pointers, greedy, binary lifting, implementation
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
const int N = 500000 + 5;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    vector<ii> P(n), Q(m);
    for (auto& i : P) cin >> i.ff >> i.ss;
    for (auto& i : Q) cin >> i.ff >> i.ss;
    sort(P.begin(), P.end());
    int MAXLOG = 31 - __builtin_clz(N);
    vector<vector<int>> st(N, vector<int>(MAXLOG+1));
    int j = 0;
    rep(i,0,N) {
        st[i][0] = -1;
        if (i > 0 and st[i-1][0] > i) st[i][0] = max(st[i][0], st[i-1][0]);
        while (j < n and P[j].ff <= i) {
            if (P[j].ss > i) st[i][0] = max(st[i][0], P[j].ss);
            ++j;
        }
    }
    rep(e,1,MAXLOG+1) rep(i,0,N) {
        int j = st[i][e-1];
        st[i][e] = (j == -1 ? -1 : st[j][e-1]);
    }
    for (auto& q : Q) {
        int l = q.ff, r = q.ss;
        int count = 0;
        invrep(e, MAXLOG, 0) if (st[l][e] != -1 and st[l][e] <= r) {
            l = st[l][e], count += 1 << e;
        }
        if (l < r and st[l][0] != -1) l = st[l][0], count++;
        if (l < r) count = -1;
        cout << count << '\n';
    }
    return 0;
}