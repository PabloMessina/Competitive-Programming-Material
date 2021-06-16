// tags: dp, math, knapsack
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
int n;
int a[100];
int memo[100][100001];
int dp(int i, int w) {
    if (i == n) return 0;
    int& ans = memo[i][w];
    if (ans != -1) return ans;
    ans = dp(i+1, w);
    if (a[i] <= w) ans = max(ans, a[i] + dp(i+1, w-a[i]));
    return ans;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n;
    int g = 0, sum = 0;
    rep(i,0,n) { 
        cin >> a[i];
        g = __gcd(g, a[i]);
        sum += a[i];
    }
    rep(i,0,n) a[i] /= g;
    sum /= g;
    if (sum & 1) { cout << "0\n"; return 0; }
    rep(i,0,n) rep(w,0,sum/2+1) memo[i][w] = -1;
    if (dp(0, sum/2) != sum/2) { cout << "0\n"; return 0; }
    rep(i,0,n) {
        if (a[i] & 1) { cout << "1\n"; cout << i+1 << '\n'; return 0; }
    }
    assert (false);
    return 0;
}