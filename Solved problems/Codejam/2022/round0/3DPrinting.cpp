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
    vector<int> c1(4), c2(4);
    rep(k,1,t+1) {
        rep(i,0,4) c1[i] = 1000000;
        rep(i,0,4) { int x; cin >> x; c1[i] = min(c1[i], x); }
        rep(i,0,4) { int x; cin >> x; c1[i] = min(c1[i], x); }
        rep(i,0,4) { int x; cin >> x; c1[i] = min(c1[i], x); }
        int sum = 0;
        rep(i,0,4) {
            c2[i] = min(1000000 - sum, c1[i]);
            sum += c2[i];
        }
        cout << "Case #" << k << ":";
        if (sum == 1000000) {
            rep(i,0,4) cout << " " << c2[i];
        } else {
            cout << " IMPOSSIBLE";
        }
        cout << '\n';
    }
    return 0;
}