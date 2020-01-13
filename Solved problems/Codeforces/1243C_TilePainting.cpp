// tags: math, number theory, CRT
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
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    ll n; cin >> n;
    int count = 0;
    ll p = 1;
    for (ll x = 2, m = n; x * x <= m; ++x) {
        if (n % x == 0) {
            count++;
            p = x;
            do { n /= x; } while (n % x == 0);
        }
    }
    if (n > 1) {
        p = n;
        count++;
    }
    if (count > 1) {
        cout << "1\n";
    } else {
        cout << p << '\n';
    }
    return 0;
}