// tags: implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int main() {
    int T; cin >> T;
    while (T--) {
        // read first polynomial
        int dg1; cin >> dg1;
        vector<int> poly1(dg1 + 1);
        rep(i,0,dg1) cin >> poly1[i];
        // read second polynomial
        int dg2; cin >> dg2;
        vector<int> poly2(dg2 + 1);
        rep(i,0,dg2) cin >> poly2[i];
        // compute polynomial multiplication
        int dg3 = dg1 + dg2;
        vector<int> poly3(dg3 + 1, 0);
        rep(i,0,dg1) rep(j,0,dg2) {
            poly3[i + j] += poly1[i] * poly2[j];
        }
        // print output
        cout << dg3 << '\n';
        rep(i,0,dg3) {
            if (i) cout << " ";
            cout << poly3[i];
        }
        cout << '\n';
    }
    return 0;
}