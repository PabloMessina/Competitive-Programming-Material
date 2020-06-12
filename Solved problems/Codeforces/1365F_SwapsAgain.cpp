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
int a[500], b[500];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    nextcase:
    while (t--) {
        int n; cin >> n;
        rep(i,0,n) cin >> a[i];
        rep(i,0,n) cin >> b[i];
        vector<pair<int,int>> ap, bp;
        int m = n/2;        
        if ((n&1) and a[m] != b[m]) {
            cout << "No\n";
            goto nextcase;
        }
        rep(i,0,m) {
            int j = n-i-1;
            ap.emplace_back(min(a[i], a[j]), max(a[i], a[j]));
            bp.emplace_back(min(b[i], b[j]), max(b[i], b[j]));
        }
        sort(ap.begin(), ap.end());
        sort(bp.begin(), bp.end());
        rep(i,0,m) if (ap[i] != bp[i]) {
            cout << "No\n";
            goto nextcase;
        }
        cout << "Yes\n";
    }
    return 0;
}