// tags: strings, rolling hashing
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
typedef unsigned long long int ull;
// -------------------------------
const int MAXLEN = 500000;
const string valid_chars = "abcdefghijklmnopqrstuvwxyz,._";

struct RH { // rolling hashing
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
    void init(vector<int>& s) {
        len = s.size();
        rep(a,0,1) {
            h[a].resize(len);
            h[a][0] = s[0];
            rep(i,1,len-1) h[a][i] = add(mul(h[a][i-1], B, a),s[i], a);
        }
    }
    RH(vector<int>& s) { init(s); }
    RH(string& s, char ref) {
        vector<int> ss(s.size());
        rep(i,0,s.size()-1) ss[i] = s[i] - ref;
        init(ss);
    }
    ull hash(int i, int j, int a) {
        if (i == 0) return h[a][j];
        return add(h[a][j], P[a] - mul(h[a][i-1], pow[a][j-i+1], a), a);
    }
    ull hash(int i, int j) {
        return hash(i,j,0) << 32 | hash(i,j,1);
    }
    ull hash() { return hash(0, len-1); }
    ull hash_index_replaced(int i, ull new_val, int a) {
        ull h_aft = i+1 <= len-1 ? hash(i+1, len-1, a) : 0;
        ull h_bef = i-1 >= 0 ? hash(0, i-1, a) : 0;
        ull new_h = mul(h_bef, pow[a][len-i], a);
        new_h = add(new_h, mul(new_val, pow[a][len-i-1], a), a);
        new_h = add(new_h, h_aft, a);
        return new_h;
    }
    ull hash_index_replaced(int i, ull new_val) {
        return hash_index_replaced(i, new_val, 0) << 32 |
                hash_index_replaced(i, new_val, 1);
    }
};
const ull RH::P[2] = {(ull)1e9+7, (ull)1e9+9};
ull RH::pow[2][MAXLEN];

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);    
    RH::init();
    char cmin = *min_element(valid_chars.begin(), valid_chars.end());    
    int N, R, M;
    string text;
    cin >> N >> text >> R >> M;
    RH rh_text(text, cmin);
    int count = 0;
    uset<ull> hashes;
    rep(i, 0, R-1) {
        string query; cin >> query;
        RH rh(query, cmin);
        rep(i,0,M-1) {
            for (char c : valid_chars) {
                ull hash = rh.hash_index_replaced(i, c - cmin);
                hashes.insert(hash);
            }
        }
        rep(i,0,N-M) {
            ull hash = rh_text.hash(i, i+M-1);
            if (hashes.count(hash)) count++;
        }
        hashes.clear();
    }
    cout << count << '\n';
    return 0;
}