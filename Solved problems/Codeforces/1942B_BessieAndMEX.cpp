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
const int MAXN = 2e5 + 7;
int a[MAXN];
int p[MAXN];
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        rep(i,0,n) cin >> a[i];
        set<int> available_values;
        rep(i,0,n+1) available_values.insert(i);
        rep(i,0,n) {
            if (a[i] < 0) {
                int x = *available_values.begin() - a[i];
                available_values.erase(x);
                p[i] = x;
            } else if (a[i] == 0) {
                assert(false); // should not happen
            } else {
                // assert(a[i] == 1);
                int x = *available_values.begin();
                available_values.erase(x);
                p[i] = x;
            }
            if (i) cout << ' ';
            cout << p[i];
        }
        cout << '\n';
    }
    return 0;
}