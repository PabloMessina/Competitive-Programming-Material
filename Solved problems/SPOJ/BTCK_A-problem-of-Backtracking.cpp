// tags: backtracking + pruning, bitwise operations, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,a,b) for(int i = a; i >= b; --i)
typedef long long int ll;
// -------------------------------

ll _pow10[10];
ll best_perm;
ll weights[10];
ll K;

void _search(int mask, int i, ll accsum, ll accperm) {
    if (accsum > K) return;
    if (accperm > best_perm) return;
    if (i == 10) {
        if (accperm < best_perm) best_perm = accperm;
    } else {
        for (int b=1, j=0; j < 10; ++j, b<<=1) {
            if ((mask & b) == 0) {
                _search(mask | b, i+1, accsum + j * weights[i], accperm + j * _pow10[9-i]);
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    _pow10[0] = 1;
    rep(i,1,9) _pow10[i] = _pow10[i-1] * 10;
    while (T--) {
        rep(i,0,9) cin >> weights[i];
        cin >> K;
        best_perm = LLONG_MAX;
        _search(0,0,0,0);
        if (best_perm == LLONG_MAX) cout << "-1\n";
        else {
            ll tmp = best_perm;
            invrep(i,9,0) {
                cout << tmp / _pow10[i];
                if (i) cout << " ";
                tmp %= _pow10[i];
            }
            cout << '\n';
        }
    }
    return 0;
}