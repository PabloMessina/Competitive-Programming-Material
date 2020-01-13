// tags: implementation
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
    int k; cin >> k;
    vector<int> a;
    a.reserve(1000);
    while (k--) {
        int n; cin >> n;
        a.resize(n);
        for (int& x : a) cin >> x;
        sort(a.begin(), a.end(), greater<int>());
        int i = 0;
        while (i+1 < n and a[i+1] >= i+2) ++i;
        cout << i+1 << '\n';
    }
    return 0;
}