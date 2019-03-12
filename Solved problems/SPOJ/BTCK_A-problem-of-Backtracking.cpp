// tags: backtracking + pruning, bitwise operations, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

ll weights[10];
int permutation[10];
ll K;

// i = index in the permutation list we are currently at
// mask = an int whose bits indicate the digits used in the permutation
//     examples:
//            0000000000 means no digits have been used yet
//            0000000001 means 0 is already used
//            0000001010 means 1 and 3 are already used
//            1000000000 means 9 is already used
// accsum = sum { permutation[k] * weights[k] for 0 <= k < i }
bool solve(int i, int mask, ll accsum) {
    if (accsum > K) return false; // more than K -> stop exploring
    if (i == 10) return true; // out of range -> we are done
    for (int b=1, j=0; j < 10; ++j, b<<=1) { // try all available digits in lexicographic order
        if ((mask & b) == 0) { // if j-th digits has not been used yet (i.e. it's available)
            permutation[i] = j;
            if (solve(i+1, mask | b, accsum + j * weights[i])) return true;
        }
    }
    return false; // nothing worked
}

int main() {
    // for faster input/output
    ios::sync_with_stdio(false);
    cin.tie(0);
    //----------------
    int T; cin >> T;
    while (T--) { // for each test case
        rep(i,0,9) cin >> weights[i]; // read weights
        cin >> K; // read K
        if (solve(0,0,0)) { // if backtracking works
            rep(i,0,9) { // print solution
                if (i) cout << " ";
                cout << permutation[i];
            }
            cout << '\n';
        } else cout << "-1\n";
    }
    return 0;
}