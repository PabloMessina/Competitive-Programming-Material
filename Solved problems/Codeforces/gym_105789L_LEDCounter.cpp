#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i < b; ++i)

string digits[10] = {
    "GGGgGGG",
    "gggggGG",
    "gGGGGGg",
    "ggGGGGG",
    "GggGgGG",
    "GgGGGgG",
    "GGGGGgG",
    "ggGggGG",
    "GGGGGGG",
    "GgGGGGG",
};

signed main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    string x;
    rep(i,0,N) {
        cin >> x;
        int count = 0;
        int found_digit = -1;
        rep(d,0,10) {
            bool match = true;
            rep(j,0,7) {
                if ((x[j] == 'g' or x[j] == 'G') and x[j] != digits[d][j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                count++;
                found_digit = d;
            }
        }
        if (count == 1) {
            cout << found_digit;
        } else {
            cout << '*';
        }
    }
    cout << '\n';
    return 0;
}