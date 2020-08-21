// tags: simulation, implementation, adhoc, modular arithmetics
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
int N, Q;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> Q;
    int maxv = INT_MIN;
    deque<int> d(N);
    rep(i,0,N) {
        cin >> d[i];
        maxv = max(maxv, d[i]);
    }
    vector<pair<int,int>> pairs;
    pairs.reserve(N);
    while (d.front() != maxv) {
        int a = d.front(); d.pop_front();
        int b = d.front(); d.pop_front();
        pairs.emplace_back(a,b);
        if (a <= b) swap(a,b);
        d.push_front(a);
        d.push_back(b);
    }
    while (Q--) {
        ll m; cin >> m; --m;
        if (m < pairs.size()) {
            auto& p = pairs[m];
            cout << p.first << ' ' << p.second << '\n';
        } else {
            int i = (m - pairs.size()) % (N-1) + 1;
            cout << maxv << ' ' << d[i] << '\n';
        }
    }
    return 0;
}