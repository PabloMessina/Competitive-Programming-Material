// tags: implementation, sorting, binary search
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
    int n; cin >> n;
    vector<int> a, b;
    a.reserve(n);
    b.reserve(n);
    rep(i,0,n) {
        int _min = INT_MAX;
        int _max = INT_MIN;
        int l; cin >> l;
        int bef = INT_MAX;
        bool is_dec = true;
        while (l--) {
            int tmp; cin >> tmp;
            if (bef < tmp) is_dec = false;
            _min = min(_min, tmp);
            _max = max(_max, tmp);
            bef = tmp;
        }
        assert (_min <= _max);
        if (is_dec) {
            a.push_back(_min);
            b.push_back(_max);
        }
    }
    ll count = 0;
    sort(b.begin(), b.end());
    for (int x : a) {
        int l = 0, r = b.size();
        while (l < r) {
            int m = (l+r)/2;
            if (b[m] > x) {
                r = m;
            } else {
                l = m+1;
            }
        }
        count += b.size() - l;
    }
    count += (ll)a.size() * (ll)(n - a.size());
    count += (ll)(n - a.size()) * (ll)n;
    cout << count << '\n';
    return 0;
}