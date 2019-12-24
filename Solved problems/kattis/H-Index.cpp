// tags: implementation, sorting, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> x(n);
    rep(i,0,n) cin >> x[i];
    sort(x.begin(), x.end(), greater<int>());
    int ans = 0;
    rep(i,0,n) {
        if (x[i] >= i+1) ans = i+1;
        else break;
    }
    cout << ans << '\n';
    return 0;
}