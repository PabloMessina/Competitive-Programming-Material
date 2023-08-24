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
ll P[26][26];
string S;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    rep(i,0,26) rep(j,0,26) cin >> P[i][j];
    rep(i,0,26) P[i][i] = 0;
    cin >> S;
    // Floyd-Warshall
    rep(k,0,26) rep(i,0,26) rep(j,0,26) {
        P[i][j] = min(P[i][j], P[i][k] + P[k][j]);
    }
    // answer
    int i = 0, j = S.size() - 1;
    ll ans = 0;
    while (i < j) {
        if (S[i] != S[j]) {
            ll tmp = LLONG_MAX;
            rep(k,0,26) {
                tmp = min(tmp, P[S[i] - 'a'][k] + P[S[j] - 'a'][k]);
            }
            ans += tmp;
        }
        ++i, --j;
    }
    cout << ans << '\n';
    return 0;
}