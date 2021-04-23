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
int memo[1000][2];
int x, y; string s; int n;
int cost(int i) {
    int ans = 0;
    if (i > 0 and s[i-1] == 'C' and s[i] == 'J') ans += x;
    if (i > 0 and s[i-1] == 'J' and s[i] == 'C') ans += y;
    if (i < n-1 and s[i] == 'C' and s[i+1] == 'J') ans += x;
    if (i < n-1 and s[i] == 'J' and s[i+1] == 'C') ans += y;
    return ans;    
}
int dp(int i, int p) {
    if (i == n) return 0;
    int& ans = memo[i][p];
    if (ans != INT_MIN) return ans;
    if (s[i] != '?') return ans = dp(i+1, s[i] == 'C');
    s[i] = 'C';
    int op1 = cost(i) + dp(i+1, 0);
    s[i] = 'J';
    int op2 = cost(i) + dp(i+1, 1);
    s[i] = '?';
    return ans = min(op1, op2);
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(_case, 1, T+1) {        
        cin >> x >> y >> s; n = s.size();
        int base = 0;
        rep(i,0,n-1) {
            if (s[i] == 'C' and s[i+1] == 'J') base += x;
            if (s[i] == 'J' and s[i+1] == 'C') base += y;
        }
        rep(i,0,n) rep(j,0,2) memo[i][j] = INT_MIN;
        cout << "Case #" << _case << ": "  << (base + dp(0, 0)) << '\n';
    }
    return 0;
}