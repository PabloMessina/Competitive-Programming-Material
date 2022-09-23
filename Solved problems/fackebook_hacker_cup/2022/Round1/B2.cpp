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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
ll MOD = 1000000000 + 7;
ll mul(ll x, ll y) { return (x * y) % MOD; }
ll add(ll x, ll y) { return (x + y) % MOD; }
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(_t,1,T+1) {
        int N, Q;
        cin >> N;
        ll x_sum = 0, x2_sum = 0, y_sum = 0, y2_sum = 0;
        rep(i,0,N) {
            ll x, y; cin >> x >> y;
            x_sum = add(x_sum, x);
            y_sum = add(y_sum, y);
            x2_sum = add(x2_sum, mul(x, x));
            y2_sum = add(y2_sum, mul(y, y));
        }
        ll ans = 0;
        cin >> Q;
        rep(i,0,Q) {
            ll x, y; cin >> x >> y;
            ans = add(ans, add(add(mul(N, mul(x,x)), MOD - mul(mul(2, x), x_sum)), x2_sum));
            ans = add(ans, add(add(mul(N, mul(y,y)), MOD - mul(mul(2, y), y_sum)), y2_sum));
        }
        cout << "Case #" << _t << ": " << ans << '\n';
    }
    return 0;
}