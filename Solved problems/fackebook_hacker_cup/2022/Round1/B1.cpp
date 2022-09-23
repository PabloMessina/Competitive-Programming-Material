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
        vector<ll> distX(3001, 0), distY(3001, 0);
        vector<ll> cX(3001, 0), cY(3001, 0);
        rep(i,0,N) {
            int x, y; cin >> x >> y;
            cX[x]++, cY[y]++;
        }
        rep(x,0,3001) {
            if (cX[x] > 0) {
                rep(xx,0,3001) {
                    distX[xx] = add(distX[xx], mul(mul(xx - x, xx - x), cX[x]));
                }
            }
        }
        rep(y,0,3001) {
            if (cY[y] > 0) {
                rep(yy,0,3001) {
                    distY[yy] = add(distY[yy], mul(mul(yy - y, yy - y), cY[y]));
                }
            }
        }
        ll ans = 0;
        cin >> Q;
        rep(i,0,Q) {
            int x, y; cin >> x >> y;
            ans = add(ans, distX[x]);
            ans = add(ans, distY[y]);
        }
        cout << "Case #" << _t << ": " << ans << '\n';
    }
    return 0;
}