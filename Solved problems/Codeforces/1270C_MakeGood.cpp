// tags: xor, bitwise, adhoc
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
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        ll s, x, a;
        s = 0, x = 0;
        while (n--) {
            cin >> a;
            s += a;
            x ^= a;
        }
        ll A = (1LL << 50) + (x&1LL);
        s += A;
        x ^= A;
        ll B = ((x << 1) - s) >> 1;
        cout << "3\n";
        cout << A << ' ' << B << ' ' << B << '\n';
        assert (s + B + B == 2LL * (x ^ B ^ B));
    }
    return 0;
}