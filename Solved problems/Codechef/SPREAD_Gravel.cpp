// tags: fenwick tree
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
int N, M;
ll C;
struct BIT {
    vector<ll> bit;
    BIT() { bit.assign(N+1, 0); }
    void add(int i, ll d) {
        for (; i < bit.size(); i += (i & -i)) bit[i] += d;
    }
    ll psq(int i) {
        ll sum = 0;
        for (; i; i -= (i & -i)) sum += bit[i];
        return sum;
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> C;
    BIT bit;
    bit.add(1, C);
    while (M--) {
        string op; cin >> op;
        if (op == "S") {
            int l, r; ll k;
            cin >> l >> r >> k;
            bit.add(l, k); bit.add(r+1, -k);
        } else {
            int p; cin >> p;
            cout << bit.psq(p) << '\n';
        }
    }
    return 0;
}