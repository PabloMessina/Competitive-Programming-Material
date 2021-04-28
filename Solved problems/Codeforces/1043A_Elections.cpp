// implementation
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
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    vector<int> a(n);
    int s = 0;
    for (int& x : a) { cin >> x; s += x; }
    int k = *max_element(a.begin(), a.end());
    while (k*n - s <= s) ++k;
    cout << k << '\n';
    return 0;
}