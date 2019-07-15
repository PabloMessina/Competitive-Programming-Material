// tags: lcm, least common multiple, gcd, brute force,
// number theory, math
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef long long int ll;

ll lcm(ll a, ll b) {
    return (a / __gcd(a,b)) * b;
}
ll lcm(ll a, ll b, ll c) {
    ll x = a;
    if (b > 0) x = lcm(x, b);
    if (c > 0) x = lcm(x, c);
    return x;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    ll ans;
    if (n&1) {
        ans = lcm(n, n-1, n-2);
    } else {
        ans = lcm(n-1, n-2, n-3);
        rep(i,2,30) {
            ans = max(ans, lcm(n, n-1, n-i));
        }
        rep(i,3,30) {
            ans = max(ans, lcm(n, n-2, n-i));
        }
    }
    cout << ans << '\n';
    return 0;
}