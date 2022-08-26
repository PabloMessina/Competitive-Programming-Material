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
    int t; cin >> t;
    rep(k,1,t+1) {
        int ans = 0;
        int n; cin >> n;
        vector<int> c(n);
        rep(i,0,n) cin >> c[i];
        sort(c.begin(), c.end());
        int j = 1;
        rep(i,0,n) if (j <= c[i]) ans++, j++;
        cout << "Case #" << k << ": " << ans << '\n';
    }
    return 0;
}