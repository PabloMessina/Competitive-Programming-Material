// tags: binary search, implementation, brute force
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
    int t; cin >> t;
    while (t--) {
        int n; ll s;
        cin >> n >> s;
        vector<ll> a(n);
        vector<ll> acc(n);
        ll sum = 0;
        rep(i,0,n) {
            cin >> a[i];
            sum += a[i];
            acc[i] = sum;
        }        
        int skipped = -1;
        if (s < sum) {
            int best = 0;
            rep(i,0,n) {
                int l = 0, r = n;
                while (l < r) {
                    int m = (l+r) / 2;
                    ll tmp = acc[m] - (i <= m ? a[i] : 0);
                    if (tmp > s) r = m;
                    else l = m+1;
                }
                int covered = l - (i < l ? 1 : 0);
                if (best < covered) {
                    best = covered;
                    skipped = i;
                }
            }
        }
        cout << skipped + 1 << '\n';
    }
    return 0;
}