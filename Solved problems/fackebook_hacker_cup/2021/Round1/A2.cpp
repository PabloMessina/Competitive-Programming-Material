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
const ll MOD = 1000000007;
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(t,1,T+1) {
        int n; string s; cin >> n >> s;
        ll ans = 0;
        int last_x=-1, last_o=-1;
        rep(i,0,n) {
            if (s[i] == 'O') {
                if (last_x > last_o) ans = (ans + (ll)(last_x+1) * (ll)(n - i)) % MOD;
                last_o = i;
            } else if (s[i] == 'X') {
                if (last_o > last_x) ans = (ans + (ll)(last_o+1) * (ll)(n - i)) % MOD;
                last_x = i;
            }
        }
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}