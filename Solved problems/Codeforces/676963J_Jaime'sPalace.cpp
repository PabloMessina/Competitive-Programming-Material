#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
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
signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int P, D; cin >> P >> D;
    vector<int> K(D);
    rep(i,0,D) cin >> K[i];
    vector<int> state(P, 0);
    int ans = 0;
    rep(i,0,D) {
        rep(j,0,K[i]) {
            state[j]++;
            ans = max(ans, state[j]);
        }
        sort(state.begin(), state.begin() + K[i]);
    }
    cout << ans << '\n';
    return 0;
}