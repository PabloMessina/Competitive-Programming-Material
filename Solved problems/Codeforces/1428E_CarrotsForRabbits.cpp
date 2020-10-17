// tags: greedy, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
ll cost(ll x, ll k) {
    ll q = x / k;
    ll r = x % k;
    return q * q * (k - r) + (q + 1) * (q + 1) * r;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, k; cin >> n >> k;
    priority_queue<tuple<ll, int>> q;
    vector<ll> X(n);
    vector<ll> divs(n, 1);
    rep(i,0,n) {
        cin >> X[i];
        if (X[i] > divs[i]) {
            q.emplace(cost(X[i], divs[i]) - cost(X[i], divs[i]+1), i);
        }
    }
    int t = k - n;
    while (t--) {
        ll x; int i; tie(x, i) = q.top(); q.pop();
        divs[i]++;
        if (X[i] > divs[i]) {
            q.emplace(cost(X[i], divs[i]) - cost(X[i], divs[i]+1), i);
        }
    }
    ll ans = 0;
    rep(i,0,n) ans += cost(X[i], divs[i]);
    cout << ans << '\n';
    return 0;
}