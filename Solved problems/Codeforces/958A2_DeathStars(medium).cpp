#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef unsigned long long int ull;
// -------------------------------
const int MAXLEN = 2000 * 200 + 5;
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
        // for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        rep(a,0,2) {
            h[a].resize(len);
            h[a][0] = s[0];
            rep(i,1,len) h[a][i] = add(mul(h[a][i-1], B, a), s[i], a);
        }
    }
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
// these lines are necessary for the code to compile
const ull RH::P[2] = {(ull)1e9+21, (ull)1e9+9};
ull RH::pow[2][MAXLEN];

int N, M;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    RH::init();
    cin >> N >> M;
    string A, tmp;
    A.reserve(N * M);
    vector<RH> rha, rhb;
    rep(_,0,N) { cin >> tmp; rha.push_back(RH(tmp)); }
    rep(_,0,M) { cin >> tmp; rhb.push_back(RH(tmp)); }    
    rep(i,0,N-M+1) {
        rep(j,0,N-M+1) {
            bool match = true;
            rep(k,0,M) if (rha[i+k].hash() != rhb[k].hash(j, j+M-1)) { match = false; break; }
            if (match) {
                cout << (i+1) << ' ' << (j+1) << '\n';
                return 0;
            }
        }
    }
    assert (false);
    return 0;
}