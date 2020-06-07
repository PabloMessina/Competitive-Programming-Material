// tags: implementation
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
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n; cin >> n;
    map<int,int> am, bm;
    rep(i,0,n) {
        int x; cin >> x;
        am.emplace(x, i);
    }
    rep(i,0,n) {
        int x; cin >> x;
        bm.emplace(x, i);
    }
    int ans = 0;
    map<int,int> counts;
    rep(i,1,n+1) {
        int d1 = (n + am[i] - bm[i]) % n;
        int d2 = d1 - n;
        counts[d1]++;
        counts[d2]++;
        ans = max({ans, counts[d1], counts[d2]});
    }
    cout << ans << '\n';
    return 0;
}