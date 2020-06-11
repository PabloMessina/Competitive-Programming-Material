// tags: brute force, bitwise, implementation
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
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int n, m, k;
vector<ll> a;
vector<int> counts;
ll ans;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> n;
    a.resize(n);
    rep(i,0,n) cin >> a[i];
    ll ans = 0;
    rep(i,0,n) {
        ans = max(ans, a[i]);
        rep(j,i+1,n) {
            ans = max(ans, a[i] | a[j]);
            rep(k,j,n) {
                ans = max(ans, a[i] | a[j] | a[k]);
            }
        }
    }
    cout << ans << '\n';
    return 0;
}