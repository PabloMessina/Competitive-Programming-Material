// tags: implementation
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
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    nextcase:
    while (t--) {
        int n; cin >> n;
        vector<int> a(n), b(n);
        for (int& x: a) cin >> x;
        int c[2] = {0};
        for (int& x: b) { cin >> x; c[x]++; }
        if (c[0] and c[1]) cout << "Yes\n";
        else {
            rep(i,1,n) if (a[i-1] > a[i]) {
                cout << "No\n"; goto nextcase;
            }
            cout << "Yes\n";
        }
    }
    return 0;
}