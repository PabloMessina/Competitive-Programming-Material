// tags: dp, strings, rolling hashing
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef unsigned long long ull;
// -------------------------------
const int MAXLEN = 1e5;
struct RH { // rolling hashing
    static const ull B = 131; // base
    static const ull P[2]; // primes
    static ull pow[2][MAXLEN];    
    static ull add(ull x, ull y, int a) { return (x + y) % P[a]; }
    static ull mul(ull x, ull y, int a) { return (x * y) % P[a]; }
    static void init(int a) {
        pow[a][0] = 1;
        rep(i,1,MAXLEN) pow[a][i] =  mul(B, pow[a][i-1], a);
    }
    static void init() { init(0); init(1); }    
    vector<ull> h[2];
    int len;
    void init(vector<int>& s) {
        len = s.size();
        rep(a,0,2) {
            h[a].resize(len);
            h[a][0] = s[0];
            rep(i,1,len) h[a][i] = add(mul(h[a][i-1], B, a), s[i], a);
        }
    }
    RH(){}
    RH(vector<int>& s) { init(s); } // from vector<int>
    RH(string& s, char ref = 'a') { // from string
        vector<int> tmp; for (char c : s) tmp.push_back(c - ref + 1);
        init(tmp);
    }
    ull hash(int i, int j, int a) {
        if (i == 0) return h[a][j];
        return add(h[a][j], P[a] - mul(h[a][i-1], pow[a][j-i+1], a), a);
    }
    ull hash(int i, int j) {
        return hash(i,j,0) << 32 | hash(i,j,1);
    }
    ull hash() { return hash(0, len-1); }
};
const ull RH::P[2] = {(ull)1e9+21, (ull)1e9+9};
ull RH::pow[2][MAXLEN];

RH rhf, rhb;
int n;
int memo[5000][5000];
int dp(int i, int j) {
    int& ans = memo[i][j];
    if (ans != -1) return ans;
    if (i > j) return ans = 0;
    if (i == j) return ans = 1;
    return ans = dp(i,j-1) + dp(i+1,j) - dp(i+1, j-1) + (rhf.hash(i, j) == rhb.hash(n-1-j, n-1-i));
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    RH::init();
    string s; cin >> s;
    n = s.size();
    rhf = RH(s);
    reverse(s.begin(), s.end());
    rhb = RH(s);
    int q; cin >> q;
    memset(memo, -1, sizeof memo);
    while (q--) {
        int l, r; cin >> l >> r; --l, --r;
        cout << dp(l, r) << '\n';
    }
    return 0;
}