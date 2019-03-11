// tags: backtracking + pruning, bitwise operations, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,a,b) for(int i = a; i >= b; --i)
typedef long long int ll;
// -------------------------------

ll weights[10];
int permutation[10];
ll K;

bool solve(int mask, int i, ll accsum) {
    if (accsum > K) return false;
    if (i == 10) return true;
    for (int b=1, j=0; j < 10; ++j, b<<=1) {
        if ((mask & b) == 0) {
            permutation[i] = j;
            if (solve(mask | b, i+1, accsum + j * weights[i])) return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    int T; cin >> T;
    while (T--) {
        rep(i,0,9) cin >> weights[i];
        cin >> K;
        if (solve(0,0,0)) {
            rep(i,0,9) {
                if (i) cout << " ";
                cout << permutation[i];
            }
            cout << '\n';
        } else cout << "-1\n";
    }
    return 0;
}