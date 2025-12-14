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
    while (t--) {
        int n, k; cin >> n >> k;
        if (n == k) {
            rep(i,0,n) {
                if (i) cout << ' ';
                cout << '1';
            }
            cout << '\n';
        } else if (k > 1) {
            cout << "-1\n";
        } else {
            rep(i,0,n) {
                if (i) cout << ' ';
                cout << i+1;
            }
            cout << '\n';
        }
    }
    return 0;
}