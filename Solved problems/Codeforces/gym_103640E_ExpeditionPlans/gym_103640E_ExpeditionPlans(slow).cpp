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
const int MAXN = 3000;
int N;
ll S[MAXN], D[MAXN], F[MAXN+1];
 
ll sail_dist(int i, int j) {
    if (i > j) swap(i, j);
    assert (j < N);
    ll s = S[j];
    if (i >= 0) s -= S[i];
    assert (s >= 0);
    return s;
}

ll memo[2][MAXN+1][MAXN+1];
ll dp_slow(int b, int l, int r) {
    assert (l <= r and r <= N);
    ll& ans = memo[b][l][r];
    if (ans != -1) return ans;
    if (l == r) return ans = F[l];
    if (r == N and b == 1) return ans = LLONG_MAX;
    int from = b == 0 ? l-1 : r;
    ans = LLONG_MAX;
    rep(i,l,r) {
        ll s = sail_dist(from, i);
        ll d = D[i];
        ll op1 = dp_slow(0, i+1, r);
        ll op2 = dp_slow(1, l, i);
        ans = min(ans, max(op1, op2) + s + d);
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    S[0] = 0;
    rep(i,1,N) {
        cin >> S[i];
        S[i] += S[i-1];
    }
    rep(i,0,N) cin >> D[i];
    rep(i,0,N+1) cin >> F[i];
    rep(k,0,2) rep(i,0,N+1) rep(j,0,N+1) memo[k][i][j] = -1;
    cout << dp_slow(0, 0, N) << '\n';
    return 0;
}