// tags: implementation, adhoc
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
// -------------------------------
int prices[200000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, p, k;
        cin >> n >> p >> k;
        rep(i,0,n) cin >> prices[i];
        sort(prices, prices + n);
        int ans = 0;
        
        // option 1
        ll acc = 0;
        int i = 0;
        while (i < n and acc + prices[i] <= p) {
            ans = max(ans, i+1);
            acc += prices[i];
            i += 2;
        }
        if (0 >= i-1 and i-1 < n and acc + prices[i-1] <= p) ans = max(ans, i);
        
        // option 2
        acc = 0;
        i = 1;
        while (i < n and acc + prices[i] <= p) {
            ans = max(ans, i+1);
            acc += prices[i];
            i += 2;
        }
        if (0 >= i-1 and i-1 < n and acc + prices[i-1] <= p) ans = max(ans, i);

        cout << ans << '\n';
    }
    return 0;
}