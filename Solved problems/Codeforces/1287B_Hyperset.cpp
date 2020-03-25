// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define uset unordered_set
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<string> cards(n);
    uset<string> cards_set;
    for (string& s : cards) {
        cin >> s; cards_set.insert(s);
    }
    int ways = 0;
    rep(i,0,n) rep(j,i+1,n) {
        string q(k, 0);
        rep(s,0,k) {
            if (cards[i][s] == cards[j][s]) {
                q[s] = cards[i][s];
            } else {
                for (char c : "SET") {
                    if (cards[i][s] != c and cards[j][s] != c) {
                        q[s] = c;
                        break;
                    }
                }
            }
        }
        ways += cards_set.count(q);
    }
    cout << ways/3 << '\n';
    return 0;
}