// tags: divide and conquer, dp, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------
umap<ll, ll> memo_ones;
ll get_ones(ll n) {
    auto it = memo_ones.find(n);
    if (it != memo_ones.end()) return it->second;
    if (n == 0) return memo_ones[n] = 0;
    return memo_ones[n] = get_ones(n >> 1) * 2 + (n & 1);
}
umap<ll, ll> memo_size;
ll get_size(ll n) {
    auto it = memo_size.find(n);
    if (it != memo_size.end()) return it->second;
    if (n <= 1) return memo_size[n] = 1;
    return memo_size[n] = get_size(n >> 1) * 2 + 1;
}
ll ones_in_range(ll n, ll i, ll j, ll l, ll r) {
    if (l <= i and j <= r) return get_ones(n);
    if (l > j or r < i) return 0;
    ll x = n >> 1;
    ll y = n & 1;
    ll m = get_size(x);
    ll ans = ones_in_range(x, i, i+m-1, l, r) + ones_in_range(x, i+m+1, i+2*m, l, r);
    if (y > 0 and l <= i+m and i+m <= r) ans += 1;
    return ans;
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    ll n, l, r; cin >> n >> l >> r;
    cout << ones_in_range(n, 0, get_size(n)-1, l-1, r-1) << '\n';
    return 0;
}