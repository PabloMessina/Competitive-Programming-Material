// tags: implementation, sorting, greedy
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    // ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> h(n);
    rep(i,0,n) cin >> h[i];
    sort(h.begin(), h.end(), greater<int>());
    int ans = 0;
    rep(i,0,n) {
        if (i+1 > h[i]) break;
        ans = i+1;
    }
    cout << ans << '\n';
    return 0;
}