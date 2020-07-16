// tags: implementation, two pointers
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
    while (t--) {
        int n; cin >> n;
        vector<int> a(n);
        for (int& x : a) cin >> x;
        int i = 0, j = n-1;
        while (i < n and a[i] == i+1) ++i;
        while (j >= 0 and a[j] == j+1) --j;
        if (i <= j) {
            int sc = 0, uc = 0;        
            rep(k,i,j+1) {
                if (a[k] == k+1) sc++;
                else uc++;
            }
            if (sc and uc) cout << "2\n";
            else if (sc) cout << "0\n";
            else cout << "1\n";
        } else {
            cout << "0\n";
        }
    }
    return 0;
}