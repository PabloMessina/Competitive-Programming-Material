// tags: logic, adhoc
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
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        rep(i,0,n) cin >> a[i];
        bool yes = false;
        int j;
        rep(i,0,n-1) {
            if (abs(a[i] - a[i+1]) >= 2) {
                yes = true;
                j = i;
                break;
            }
        }
        if (yes) {
            cout << "YES\n";
            cout << j+1 << ' ' << j+2 << '\n';
        }
        else cout << "NO\n";
    }
    return 0;
}