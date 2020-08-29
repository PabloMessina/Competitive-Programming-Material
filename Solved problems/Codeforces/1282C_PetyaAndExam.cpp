// tags: implementation, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define ff first
#define ss second
typedef pair<int,int> ii;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int m; cin >> m;
    while (m--) {
        int n; ll T, a, b; cin >> n >> T >> a >> b;
        vector<ii> P(n);
        for (auto& p : P) cin >> p.ss;
        for (auto& p : P) cin >> p.ff;
        sort(P.begin(), P.end());
        int nh = 0, ne = 0;
        for (auto& p : P) { if (p.ss) nh++; else ne++; }
        if (ne * a + nh * b <= T) {
            cout << n << '\n'; continue;
        }
        int i = 0, h = 0, e = 0;
        int ans = 0;
        while (i < n) {
            ll t = P[i].ff - 1;
            t -= e * a + h * b;
            if (t >= 0) {
                int ke = min(t / a, (ll)(ne - e));
                t -= ke * a;
                int kh = min(t / b, (ll)(nh - h));
                ans = max(ans, e + h + ke + kh);
            }
            do {
                if (P[i++].ss) h++; else e++;
            } while (i < n and P[i].ff == P[i-1].ff);
        }
        cout << ans << '\n';
    }
    return 0;
}