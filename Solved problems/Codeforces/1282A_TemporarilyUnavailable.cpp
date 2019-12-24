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
typedef vector<int> vi;
typedef pair<int,int> ii;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int a, b, c, r;
        cin >> a >> b >> c >> r;
        if (a > b) swap(a, b);
        int x = max(a, c - r);
        int y = min(b, c + r);
        cout << b - a - max(y-x, 0) << '\n';
    }
    return 0;
}