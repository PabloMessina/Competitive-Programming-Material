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

vector<pair<ll,ll>> A, B;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int m, n; cin >> m >> n;
    
    A.resize(m); B.resize(n);
    for (auto& p : A) cin >> p.ff >> p.ss;
    for (auto& p : B) cin >> p.ff >> p.ss;

    ll ans = 0;
    for (auto& x : A) for (auto& y : B) ans = max(ans, max(y.ff - x.ff, 0ll) * max(y.ss - x.ss, 0ll));
    cout << ans << '\n';

    return 0;
}