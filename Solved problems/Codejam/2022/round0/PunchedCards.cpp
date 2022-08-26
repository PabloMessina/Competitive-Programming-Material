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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    rep(k,1,t+1) {
        cout << "Case #" << k <<":\n";
        int r,c; cin >> r >> c;
        cout << "..+";
        rep(j,1,c) cout << "-+";
        cout << '\n';
        rep(i,0,r) {
            cout << (i == 0 ? '.' : '|');
            rep(j,0,c) cout << ".|";
            cout << '\n';
            cout << '+';
            rep(j,0,c) cout << "-+";
            cout << '\n';
        }        
    }
    return 0;
}