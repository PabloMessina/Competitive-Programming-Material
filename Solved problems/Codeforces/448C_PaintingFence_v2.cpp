// tags: divide and conquer, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
ll a[5000];
ll solve(int l, int r, int h) {
    ll hmin = *min_element(a + l, a + r);
    ll ans = hmin - h;
    int i = l;
    while (i < r) {
        while (i < r and a[i] == hmin) ++i;
        int j = i;
        while (j < r and a[j] > hmin) ++j;
        if (i < j) ans += solve(i, j, hmin);
        i = j;
    }
    return min(ans, (ll)(r - l));
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n; cin >> n;
    rep(i,0,n) cin >> a[i];
    cout << solve(0, n, 0) << '\n';
    return 0;
}