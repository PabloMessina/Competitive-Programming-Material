// tags: implementation, bitmask, bitwise, std::map
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        map<string, ll> A, B;
        string name;
        rep(i,0,n) {
            cin >> name;
            int k;
            // idioma A
            cin >> k;
            rep(j,0,k) {
                cin >> name;
                A[name] |= 1LL << i;
            }
            // idioma B
            cin >> k;
            rep(j,0,k) {
                cin >> name;
                B[name] |= 1LL << i;
            }
        }
        for (auto& a : A) { // C++11
            for (auto& b : B){
                if (a.second == b.second) {
                    cout << "(" << a.first << ", " << b.first << ")\n";
                }
            }
        }
        if (t) cout << '\n';
    }
    return 0;
}