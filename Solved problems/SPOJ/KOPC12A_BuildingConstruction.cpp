// tags: binary search, ternary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 10000;
ll H[MAXN], C[MAXN], n;

ll cost(int h) {
    ll c = 0;
    rep(i,0,n) c += C[i] * abs(H[i] - h);
    return c;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        cin >> n;
        rep(i,0,n) cin >> H[i];
        rep(i,0,n) cin >> C[i];
        int max_h = *max_element(H, H+n);
        int l = 0, r = max_h;
        while (l < r) {
            int m = (l+r) >> 1;
            if (cost(m+1) >= cost(m)) r = m;
            else l = m+1;
        }
        cout << cost(l) << '\n';
    }
    return 0;
}