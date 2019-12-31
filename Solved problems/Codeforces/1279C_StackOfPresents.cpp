// tags: implementation, adhoc
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

vector<int> a, b;
vector<bool> seen;
int main() { 
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, m; cin >> n >> m;
        a.resize(n);
        rep(i,0,n) {
            cin >> a[i];
            a[i]--;
        }
        b.resize(m);
        rep(i,0,m) {
            cin >> b[i];
            b[i]--;
        }
        seen.assign(n, false);
        int last_i = 0;
        ll cost = 0;
        rep(i,0,m) {
            if (seen[b[i]]) cost++;
            else {
                while (a[last_i] != b[i]) {
                    seen[a[last_i]] = true;
                    ++last_i;
                }
                seen[b[i]] = true;
                cost += 2 * (last_i - i) + 1;
            }
        }
        cout << cost << '\n';
    }
    return 0; 
}