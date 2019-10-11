#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef unsigned long long int ull;

const int MAXLEN = 1e6;

// ------------------------------------
// rolling hashing using a single prime

struct RH_single { // rolling hashing
    static const ull B = 127; // base
    static const ull P = 1e9 + 7; // prime
    static ull pow[MAXLEN];    

    static ull add(ull x, ull y) { return (x + y) % P; }
    static ull mul(ull x, ull y) { return (x * y) % P; }

    static void init() {
        pow[0] = 1;
        rep(i, 1, MAXLEN-1) pow[i] = mul(B, pow[i-1]);
    }
    
    vector<ull> h;
    int len;
    RH_single(string& s) {
        len = s.size();
        h.resize(len);
        h[0] = s[0] - 'a';
        rep(i,1,len-1) h[i] = add(mul(h[i-1], B),s[i] - 'a');
    }

    ull hash(int i, int j) {
        if (i == 0) return h[j];
        return add(h[j], P - mul(h[i-1], pow[j - i + 1]));
    }
    ull hash() { return h[len-1]; }
};
ull RH_single::pow[MAXLEN]; // necessary for the code to compile

// -------------------------------------------------
// rolling hashing using 2 primes (for extra safety)

struct RH_double { // rolling hashing
    static const ull B = 127; // base    
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
    RH_double(string& s) {
        len = s.size();
        rep(a,0,1) {
            h[a].resize(len);
            h[a][0] = s[0] - 'a';
            rep(i,1,len-1) h[a][i] = add(mul(h[a][i-1], B, a),s[i] - 'a', a);
        }
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
const ull RH_double::P[2] = {(int)1e9+7, (int)1e9+9};
ull RH_double::pow[2][MAXLEN];


// ----- usage & testing
int main() {
    RH_single::init();
    while (true) {
        string s1, s2; cin >> s1 >> s2;
        if (s1.size() == s2.size()) {
            ull h1 = RH_single(s1).hash(0, s1.size()-1);
            ull h2 = RH_single(s2).hash(0, s2.size()-1);            
            if (s1 == s2 ? h1 == h2 : h1 != h2) {
                cout << "test passed!" << endl;
            } else {
                cout << "test failed :(" << endl;
            }
        }
    }
}