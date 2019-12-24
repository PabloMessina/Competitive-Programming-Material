// tags: DP, greedy
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
int n, p, k;
int memo[200000];
int dp(int i) {
    int& ans = memo[i];
    if (ans != -1) return ans;
    if (i == 0 or i == k-1) return ans = prices[i];
    ans = prices[i] + dp(i-1);
    if (i-k >= 0) ans = min(ans, prices[i] + dp(i-k));
    return ans;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> p >> k;
        rep(i,0,n) cin >> prices[i];
        sort(prices, prices + n);
        memset(memo, -1, sizeof(int) * n);
        int ans = 0;
        rep(i,0,n) if (dp(i) <= p) ans = i+1;
        cout << ans << '\n';
    }
    return 0;
}