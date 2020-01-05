// tags: DP
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
// -------------------------------

int n;
int perm[100];

int memo[101][2][101][101];
int dp(int i, int p, int c0, int c1) {
    int& ans = memo[i][p][c0][c1];
    if (ans != -1) return ans;
    if (i == n) {
        assert (c0 == 0 and c1 == 0);
        return ans = 0;
    }
    int cost = i > 0;
    if (perm[i] == 0) {
        assert (c0 + c1 > 0);
        ans = INT_MAX;
        if (p == 0) {            
            if (c0 > 0) {
                ans = min(ans, dp(i+1, 0, c0-1, c1));
            } 
            if (c1 > 0) {
                ans = min(ans, cost + dp(i+1, 1, c0, c1-1));
            }
        } else {
            if (c0 > 0) {
                ans = min(ans, cost + dp(i+1, 0, c0-1, c1));
            } 
            if (c1 > 0) {
                ans = min(ans, dp(i+1, 1, c0, c1-1));
            }
        }
    } else {
        ans = (((perm[i]&1) != p) ? cost : 0) + dp(i+1, perm[i]&1, c0, c1);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> n;
    vector<bool> used(n+1, 0);
    rep(i,0,n) {
        cin >> perm[i];
        used[perm[i]] = true;
    }
    int c0 = 0, c1 = 0;
    rep(k,1,n+1) {
        if (not used[k]) {
            if (k&1) c1++;
            else c0++;
        }
    }
    memset(memo, -1, sizeof memo);
    cout << dp(0, 0, c0, c1) << '\n';
    return 0;
}