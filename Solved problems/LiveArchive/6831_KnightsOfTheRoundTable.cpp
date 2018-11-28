// tags: combinatorics, math, modular arithmetics
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXK = (int)1e6;
const ll MOD = (ll)1e9 + 7;
int K,D;
bool arrived[MAXK];
bool occupied[MAXK];
int main() {
    while (cin >> K >> D) {
        memset(arrived, 0, sizeof(bool) * K);
        memset(occupied, 0, sizeof(bool) * K);
        while (D--) {
            int a, b; cin >> a >> b; --a, --b;
            arrived[a] = true;
            occupied[b] = true;
        }
        int f=0, f_min=0, i_min=0;
        rep(i,1,K-1) {
            if (!arrived[i-1]) f++;
            if (!occupied[i-1]) f--;
            if (f < f_min) {
                f_min = f;
                i_min = i;
            }
        }
        f = 0;
        ll ans = 1;
        rep(i,0,K-1) {
            int j = (i + i_min) % K;
            if (!arrived[j]) f++;
            if (!occupied[j]) {
                ans = (ans * f) % MOD;
                f--;
            }
        }
        cout << ans << '\n';
    }
    return 0;
}