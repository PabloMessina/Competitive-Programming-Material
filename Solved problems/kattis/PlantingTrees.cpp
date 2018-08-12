// tags: greedy
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int main() {
    int n; cin >> n;
    vector<int> ts(n);
    rep(i,0,n-1) cin >> ts[i];
    sort(ts.begin(), ts.end());
    int ans = 0;
    rep(i,0,n-1) ans = max(ans, ts[n-i-1] + i + 2);
    cout << ans << endl;
    return 0;
}