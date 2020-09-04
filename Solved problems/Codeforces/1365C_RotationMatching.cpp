// tags: implementation, modular arithmetic, math
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    map<int,int> am, bm;
    rep(i,0,n) {
        int x; cin >> x;
        am.emplace(x, i);
    }
    rep(i,0,n) {
        int x; cin >> x;
        bm.emplace(x, i);
    }
    int ans = 0;
    map<int,int> counts;
    rep(i,1,n+1) {
        int x = (n + am[i] - bm[i]) % n;
        counts[x]++;
        ans = max(ans, counts[x]);
    }
    cout << ans << '\n';
    return 0;
}