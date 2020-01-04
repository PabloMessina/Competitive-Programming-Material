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
    int n, m;
    cin >> n >> m;
    vector<string> s, t;
    string tmp;
    rep(i,0,n) {
        cin >> tmp;
        s.push_back(tmp);
    }
    rep(i,0,m) {
        cin >> tmp;
        t.push_back(tmp);
    }
    int q; cin >> q;
    while (q--) {
        int y; cin >> y; --y;
        cout << s[y % s.size()] << t[y % t.size()] << '\n';
    }
    return 0;
}