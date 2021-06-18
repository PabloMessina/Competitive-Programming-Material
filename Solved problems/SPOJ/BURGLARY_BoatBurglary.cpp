// tags: divide and conquer, brute force, bitmasks, implementation, binary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
ll w[30];
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    vector<pair<ll,int>> left, right;
    left.reserve(1 << 15);
    right.reserve(1 << 15);
    rep(_case, 1, t+1) {
        int n; ll d; cin >> n >> d;
        rep(i,0,n) cin >> w[i];
        cout << "Case #" << _case << ": ";
        if (n == 1) {
            if (w[0] == d) cout << 1;
            else cout << "IMPOSSIBLE\n";
        } else {
            int m = n/2;
            left.clear();
            right.clear();
            rep(mask, 0, 1 << m) {
                ll sum = 0;
                int count = 0;
                rep(j,0,m) {
                    if ((1 << j) & mask) {
                        sum += w[j];
                        count++;
                    }
                }
                left.emplace_back(sum, count);
            }
            rep(mask, 0, 1 << (n - m)) {
                ll sum = 0;
                int count = 0;
                rep(j,m,n) {
                    if ((1 << (j-m)) & mask) {
                        sum += w[j];
                        count++;
                    }
                }
                right.emplace_back(sum, count);
            }
            sort(right.begin(), right.end());
            int ans = -1;
            for (auto& p : left) {
                if (p.first <= d) {
                    int l1 = 0, r1 = right.size();
                    while (l1 < r1) { // lower bound
                        int m1 = (l1+r1) >> 1;
                        if (right[m1].first >= d - p.first) r1 = m1;
                        else l1 = m1+1;
                    }
                    int l2 = l1, r2 = right.size();
                    while (l2 < r2) { // upper bound
                        int m2 = (l2+r2) >> 1;
                        if (right[m2].first > d - p.first) r2 = m2;
                        else l2 = m2+1;
                    }
                    assert (l1 <= l2); // paranoico
                    if (l1 < l2) {
                        assert (p.first + right[l1].first == d); // paranoico
                        if (right[l1].second != right[l2-1].second) {
                            cout << "AMBIGIOUS\n"; goto nextcase;
                        }
                        if (ans != -1 and ans != p.second + right[l1].second) {
                            cout << "AMBIGIOUS\n"; goto nextcase;
                        }
                        ans = p.second + right[l1].second;
                    }
                }
            }
            if (ans != -1) cout << ans << '\n';
            else  cout << "IMPOSSIBLE\n";
        }        
        nextcase:;
    }
    return 0;
}