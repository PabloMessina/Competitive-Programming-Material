// tags: greedy, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {        
        int n; cin >> n;
        multiset<int> a, b;
        rep(i,0,n) { int x; cin >> x; a.insert(x); }
        int ans = 0;
        while (a.size() > 0) {
            if (a.size() <= 2) {
                ans += *a.rbegin();
                break;
            }
            int cost1 = *next(a.begin()) * (a.size() > 3 ? 2 : 1) + *a.begin() + *a.rbegin();
            int cost2 = *a.rbegin() + *a.begin() * (a.size() > 3 ? 2 : 1) + *next(a.rbegin());            
            if (cost1 < cost2) {
                b.insert(*a.begin());
                a.erase(a.begin());
                b.insert(*a.begin());
                a.erase(a.begin());                
                a.insert(*b.begin());
                b.erase(b.begin());
                b.insert(*a.rbegin());
                a.erase(prev(a.end()));
                b.insert(*a.rbegin());
                a.erase(prev(a.end()));
            } else {
                b.insert(*a.rbegin());
                a.erase(prev(a.end()));
                b.insert(*a.rbegin());
                a.erase(prev(a.end()));
                b.insert(*a.begin());
                a.erase(a.begin());
            }
            if (a.size() > 0) {
                a.insert(*b.begin());
                b.erase(b.begin());
            }
            ans += min(cost1, cost2);
        }
        cout << ans << '\n';
    }
    return 0;
}