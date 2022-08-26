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
const int MAXN = 1000;
const int MAXP = 100;
int N, P;
ll cost[MAXN];
ll X[MAXN][MAXP];
ll memo[MAXN][2][2];
ll dp(int i, int p, int c) {
    if (i == N) return 0;
    ll& ans = memo[i][p][c];
    if (ans != -1) return ans;
    ll base_cost = abs(X[i][0] - X[i][P-1]);
    if (i > 0) {
        ll last_p = p == 0 ? X[i-1][P-1] : X[i-1][0];
        ll first_c = c == 0 ? X[i][0] : X[i][P-1];
        base_cost += abs(last_p - first_c);
    }
    ll op1 = dp(i+1, c, 0);
    ll op2 = dp(i+1, c, 1);
    return ans = base_cost + min(op1, op2);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(k,1,T+1) {
        cin >> N >> P;
        rep(i,0,N) rep(j,0,P) cin >> X[i][j];
        rep(i,0,N) {
            sort(&X[i][0], &X[i][0] + P);
            ll c = 0;
            rep(j,1,P) c += X[i][j] - X[i][j-1];
            cost[i] = c;
        }
        rep(i,0,N) rep(j,0,2) rep(l,0,2) memo[i][j][l] = -1;
        ll op1 = dp(0, 0, 0) + X[0][0];
        ll op2 = dp(0, 0, 1) + X[0][P-1];
        ll ans = min(op1, op2);
        cout << "Case #" << k << ": " << ans << '\n';
    }
    return 0;
}