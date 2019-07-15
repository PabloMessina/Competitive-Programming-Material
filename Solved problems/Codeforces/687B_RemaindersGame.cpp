// tags: gcd, lcm, math
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
ll lcm(ll a, ll b) { return (a/__gcd(a,b))*b; }
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll n, k; cin >> n >> k;
    ll x = 1;
    rep(i,0,n-1) {
        ll c; cin >> c;
        x = lcm(x, __gcd(c, k));
    }
    if (x == k) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}