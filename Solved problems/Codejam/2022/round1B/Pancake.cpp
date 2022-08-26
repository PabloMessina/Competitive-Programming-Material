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
    int T; cin >> T;
    rep(k,1,T+1) {
        int n; cin >> n;
        vector<int> D(n);
        rep(i,0,n) cin >> D[i];
        int l = 0, r = n-1;
        int max_ = -1;
        int count = 0;
        while (l <= r) {
            int i;
            if (l == r) {
                i = l; ++l;
            } else if (D[l] < D[r]) {
                i = l; ++l;                
            } else {
                i = r; --r;
            }
            if (max_ <= D[i]) {
                count++;
                max_ = D[i];
            }
        }
        cout << "Case #" << k << ": " << count << '\n';
    }
    return 0;
}