// tags: interactive, adhoc
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
    int n, k; cin >> n >> k;
    map<int,int> f;
    rep(i,0,k+1) {
        cout << '?';
        rep(j,0,k+1) {
            if (i == j) continue;
            cout << ' ' << j+1;
        }
        cout << '\n';
        cout.flush();
        int pos, a;
        cin >> pos >> a;
        f[a]++;
    }
    cout << "! " << f.rbegin()->second << '\n';    
    return 0;
}