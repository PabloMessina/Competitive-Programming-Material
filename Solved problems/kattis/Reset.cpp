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
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; ll c;
    cin >> n >> c;
    vector<ll> ts(n), ds(n);
    ll tsum = 0;
    rep(i,0,n) {
        cin >> ts[i] >> ds[i];
        tsum += ts[i];
    }
    if (tsum <= c) {
        cout << "0\n";
        return 0;
    }
    priority_queue<tuple<int,ll,int>> q;
    rep(i,0,n) q.emplace(INT_MAX, ts[i] >= ds[i] ? ds[i] : ts[i], i);
    int ans = 0;
    while (true) {
        ll cc = c;
        // printf("----- round %d, tsum = %lld\n", ans, tsum);
        while (cc and tsum and q.size() > 0) {
            if (tsum <= cc) {
                cout << ans << '\n';
                return 0;
            }
            auto p = q.top();
            if (INT_MAX - get<0>(p) > ans) break;
            q.pop();
            int i = get<2>(p);
            assert (ts[i] > 0);
            // printf("i = %d, ts[i]=%lld, ds[i]=%lld\n", i, ts[i], ds[i]);
            ll k = ts[i] / ds[i];
            if (k == 0) {
                tsum -= ts[i];
                ts[i] = 0;
                k = 1;
                cc--;
            } else {
                // k = min(k, cc);
                // if (ds[i] > 1) {
                //     assert (tsum > cc);
                //     ll x = (tsum - cc) / (ds[i] - 1);
                //     if ((tsum - cc) % (ds[i] - 1) > 0) x += 1;
                //     k = min(k, x);
                // }
                k = 1;
                tsum -= k * ds[i];
                ts[i] -= k * ds[i];
                cc -= k;
                if (ts[i] > 0) q.emplace(INT_MAX - (ans+1), ts[i] >= ds[i] ? ds[i] : ts[i], i);
            }
            // printf("i = %d, ts[i]=%lld, ds[i]=%lld, k=%lld, tsum=%lld, cc=%lld\n", i, ts[i], ds[i], k, tsum, cc);
        }
        if (tsum <= cc) {
            cout << ans << '\n';
            return 0;
        }
        ans++;        
    }
    return 0;
}