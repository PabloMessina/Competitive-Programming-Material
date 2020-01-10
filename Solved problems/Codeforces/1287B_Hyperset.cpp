// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
ll get_mask(const string& s) {
    ll mask = 0;
    for (char c : s) {
        for (ll j = 0; j < 3; ++j) {
            if (c == "SET"[j]) {
                mask |= j;
                break;
            }
        }
        mask <<= 2;
    }
    return mask;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int n, k;
    cin >> n >> k;
    vector<string> cards(n);
    uset<ll> masks;
    for (string& s : cards) {
        cin >> s;
        masks.insert(get_mask(s));
    }
    int count = 0;
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
        count += masks.count(get_mask(q));
    }
    count /= 3;
    cout << count << '\n';
    return 0;
}