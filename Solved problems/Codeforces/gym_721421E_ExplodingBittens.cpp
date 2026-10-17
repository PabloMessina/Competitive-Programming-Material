// tags: constructive, greedy, ad hoc
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
signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int n, m, k, p; cin >> n >> m >> k >> p;
    // each bomb eliminates a distinct player other than Luigi
    if (m >= p) {
        cout << "NO\n";
        return 0;
    }
    // bombs for players 1..k-1, then a star for Luigi, then bombs for players k+1, k+2, ...
    // (at most p-k of them, so they all land before Luigi's next turn), then stars
    int before = min(k - 1, m);
    string deck = string(before, 'B') + 'E' + string(m - before, 'B');
    deck += string(n - (int)deck.size(), 'E');
    cout << "SI\n" << deck << '\n';
    return 0;
}