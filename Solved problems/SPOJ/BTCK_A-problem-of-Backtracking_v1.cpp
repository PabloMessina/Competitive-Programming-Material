// tags: brute force, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
ll X[10], D[10];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int T; cin >> T;
    loop:
    while (T--) {
        rep(i,0,10) D[i] = i;
        rep(i,0,10) cin >> X[i];
        ll K; cin >> K;
        do {
            ll sum = 0;
            rep(i,0,10) sum += D[i] * X[i];
            if (sum <= K) {
                rep(i,0,10) {
                    if (i) cout << ' ';
                    cout << D[i];
                }
                cout << '\n';
                goto loop;
            }
        } while (next_permutation(D, D+10));
        cout << "-1\n";
    }
    return 0;
}