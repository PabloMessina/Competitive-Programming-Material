// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string s, t; cin >> s >> t;
    vector<int> moves;
    rep(i,0,n) {
        if (s[i] != t[i]) {
            rep(j,i+1,n) {
                if (s[j] == t[i]) {
                    invrep(k, j-1, i) {
                        swap(s[k], s[k+1]);
                        moves.push_back(k+1);
                    }
                    break;
                }
            }
        }
    }
    if (s == t) {
        cout << moves.size() << '\n';
        rep(i,0,moves.size()) {
            if (i) cout << ' '; cout << moves[i];
        }
        cout << '\n';
    } else {
        cout << "-1\n";
    }
    return 0;
}