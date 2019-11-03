#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef unsigned long long int ull;
const int MAXLEN = 1e6;

// -----------------------------
// Rolling Hashing: single hash

struct RH_single { // rolling hashing
    static const ull B = 131; // base
    static const ull P = 1e9 + 21; // prime
    static ull pow[MAXLEN];    
    static ull add(ull x, ull y) { return (x + y) % P; }
    static ull mul(ull x, ull y) { return (x * y) % P; }
    static void init() {
        pow[0] = 1;
        rep(i, 1, MAXLEN-1) pow[i] = mul(B, pow[i-1]);
    }    
    vector<ull> h;
    int len;
    void init(vector<int>& s) {
        for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        h.resize(len);
        h[0] = s[0];
        rep(i,1,len-1) h[i] = add(mul(h[i-1], B), s[i]);
    }
    RH_single(vector<int>& s) { init(s); } // from vector<int>
    RH_single(string& s, char ref) { // from string
        vector<int> tmp; for(char c : s) tmp.push_back(c - ref + 1);
        init(tmp);
    }
    ull hash(int i, int j) {
        if (i == 0) return h[j];
        return add(h[j], P - mul(h[i-1], pow[j - i + 1]));
    }
    ull hash() { return h[len-1]; }
};
ull RH_single::pow[MAXLEN]; // necessary for the code to compile

// --------------------------------------------
// Rolling Hashing: double hash (extra safety)

struct RH_double { // rolling hashing
    static const ull B = 131; // base
    static const ull P[2]; // primes
    static ull pow[2][MAXLEN];    
    static ull add(ull x, ull y, int a) { return (x + y) % P[a]; }
    static ull mul(ull x, ull y, int a) { return (x * y) % P[a]; }
    static void init(int a) {
        pow[a][0] = 1;
        rep(i, 1, MAXLEN-1) pow[a][i] =  mul(B, pow[a][i-1], a);
    }
    static void init() { init(0); init(1); }    
    vector<ull> h[2];
    int len;
    void init(vector<int>& s) {
        for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        rep(a,0,1) {
            h[a].resize(len);
            h[a][0] = s[0];
            rep(i,1,len-1) h[a][i] = add(mul(h[a][i-1], B, a), s[i], a);
        }
    }
    RH_double(vector<int>& s) { init(s); } // from vector<int>
    RH_double(string& s, char ref) { // from string
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
const ull RH_double::P[2] = {(ull)1e9+21, (ull)1e9+9};
ull RH_double::pow[2][MAXLEN];

// ----- usage & testing
int main() {
    RH_double::init();
    while (true) {
        string s; cin >> s;
        int l1, r1, l2, r2; cin >> l1 >> r1 >> l2 >> r2;
        char cmin = *min_element(s.begin(), s.end());
        RH_double rh(s, cmin);
        ull h1 = rh.hash(l1, r1);   
        ull h2 = rh.hash(l2, r2);
        string s1 = s.substr(l1, r1-l1+1);
        string s2 = s.substr(l2, r2-l2+1);
        printf("Strings s1=%s and s2=%s are %s\n", s1.c_str(), s2.c_str(),
            h1 == h2 ? "EQUAL" : "DISTINCT");
    }
}