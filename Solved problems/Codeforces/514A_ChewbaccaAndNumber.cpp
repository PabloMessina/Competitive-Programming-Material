// tags: implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int main() {
    string num; cin >> num; // read input
    int n = num.size();
    rep(i,0,n-1) { // update each character inplace when it's correct to do so
        int x = num[i] - '0';
        if (i == 0) {
            if (5 <= x and x <= 8) {
                num[i] = (char)('0' + 9 - x);
            }
        } else if (5 <= x) {
            num[i] = (char)('0' + 9 - x);
        }
    }
    cout << num << endl; // print output
    return 0;
}