// tags: math, gcd, binary search, geometry
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
ll upper_bound(ll g, ll x, ll ref) {
    ll l = 1, r = g;
    while (l < r) {
        ll m = (l+r)>>1;
        if (m * x > ref) r = m;
        else l = m+1;
    }
    return l;
}
ll lower_bound(ll g, ll x, ll ref) {
    ll l = 1, r = g;
    while (l < r) {
        ll m = (l+r)>>1;
        if (m * x >= ref) r = m;
        else l = m+1;
    }
    return l;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll x, y, x1, y1, x2, y2;
    cin >> x >> y >> x1 >> y1 >> x2 >> y2;
    ll g = __gcd(x, y);
    x /= g, y /= g;
    ll k1 = 1;
    ll k2 = g;
    k1 = max(k1, lower_bound(g, y, y1));
    k1 = max(k1, lower_bound(g, x, x1));
    k2 = min(k2, upper_bound(g, y, y2));
    k2 = min(k2, upper_bound(g, x, x2));
    if (k1 == 1 and k2 == g) {
        cout << "Yes\n";
    } else {        
        cout << "No\n";
        ll k;
        if (k1 < k2) {
            if (k1 > 1) k = 1;
            else k = k2;
        } else {
            k = 1;
        }
        cout << x * k << ' ' << y * k << '\n';
    }
    return 0;
}