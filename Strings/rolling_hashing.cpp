/* =======================================
 * POLYNOMIAL ROLLING HASH MATH REMINDER
 * ---------------------------------------
 * A string is treated as a polynomial evaluated at a specific Base (B), 
 * modulo a Prime (P).
 * * 1. Prefix Hash Definition:
 * H[k] = (s[0]*B^k + s[1]*B^(k-1) + ... + s[k]*B^0) % P
 * * 2. Iterative Construction (used in init):
 * H[k] = (H[k-1] * B + s[k]) % P
 * * 3. Substring Hash Extraction for s[i..j] (used in hash(i, j)):
 * Hash(i, j) = (H[j] - H[i-1] * B^(length)) % P
 * = (H[j] + P - (H[i-1] * B^(j - i + 1)) % P) % P
 * * Conceptually, to get the hash of s[i..j], we take the hash of the prefix
 * ending at j, and "subtract" the prefix ending at i-1. To align the 
 * "powers" of B, we must multiply H[i-1] by B raised to the substring length.
 * ========================================== */
const int MAXLEN = 1e6;
// --------------------------------------------
// Rolling Hashing: double hash (extra safety)
struct RH_double { // rolling hashing
    static const ull B = 131; // base
    static const ull P[2]; // primes
    static ull pow[2][MAXLEN];
    static ull add(ull x, ull y, int a) { return (x + y) % P[a]; }
    static ull mul(ull x, ull y, int a) { return (x * y) % P[a]; }
    // Initializes powers of B. Call RH_double::init() once globally.
    static void init(int a) {
        pow[a][0] = 1;
        rep(i, 1, MAXLEN) pow[a][i] = mul(B, pow[a][i-1], a);
    }
    static void init() { init(0); init(1); }
    // Mathematically shifts the hash 'h' left by 'k' positions.
    // Equivalent to appending 'k' virtual characters (zeros) to the right 
    // of the string represented by 'h'. Useful for concatenating hashes.
    static ull shift_left(ull h, int k) {
        ull h0 = h >> 32;                     // a=0 is in the upper 32 bits
        ull h1 = h & ((1ull << 32) - 1);      // a=1 is in the lower 32 bits
        h0 = mul(h0, pow[0][k], 0);
        h1 = mul(h1, pow[1][k], 1);
        return (h0 << 32) | h1;
    }
    // Adds two packed hashes together
    static ull add(ull x, ull y) {
        ull x0 = x >> 32, x1 = x & ((1ull << 32) - 1);
        ull y0 = y >> 32, y1 = y & ((1ull << 32) - 1);
        ull ans0 = add(x0, y0, 0);
        ull ans1 = add(x1, y1, 1);
        return (ans0 << 32) | ans1;
    }
    vector<ull> h[2];
    int len;
    // s must be 0-indexed [0, s.size()-1]
    void init(const vector<int>& s) {
        // for (int x : s) assert (x >= 1); // DEBUGGING
        len = s.size();
        if (len == 0) return;
        rep(a, 0, 2) {
            h[a].resize(len);
            h[a][0] = s[0];
            rep(i, 1, len) h[a][i] = add(mul(h[a][i-1], B, a), s[i], a);
        }
    }
    RH_double(const vector<int>& s) { init(s); } // from vector<int>
    RH_double(const string& s, char ref = 'a') { // from string
        vector<int> tmp; 
        for (char c : s) tmp.push_back(c - ref + 1);
        init(tmp);
    }
    // Returns packed hash of substring s[i..j] (both i and j are INCLUSIVE)
    ull hash(int i, int j, int a) {
        if (i == 0) return h[a][j];
        return add(h[a][j], P[a] - mul(h[a][i-1], pow[a][j-i+1], a), a);
    }
    // Returns packed double hash of substring s[i..j] (INCLUSIVE bounds)
    ull hash(int i, int j) { return (hash(i, j, 0) << 32) | hash(i, j, 1); }
    // Returns hash of the entire string s[0..len-1] (INCLUSIVE bounds)
    ull hash() { return hash(0, len - 1); }
};

// these lines are necessary for the code to compile
const ull RH_double::P[2] = {(ull)1e9+21, (ull)1e9+9};
ull RH_double::pow[2][MAXLEN];

// ----- usage & testing
int main() {
    RH_double::init();
    string s = "abacaba";
    int l1 = 0, r1 = 2; // "aba"
    int l2 = 4, r2 = 6; // "aba"
    char cmin = *min_element(s.begin(), s.end());
    RH_double rh(s, cmin); // O(s.size())
    ull h1 = rh.hash(l1, r1); // O(1)
    ull h2 = rh.hash(l2, r2); // O(1)
    string s1 = s.substr(l1, r1 - l1 + 1);
    string s2 = s.substr(l2, r2 - l2 + 1);
    cout << "Strings s1=" << s1 << " and s2=" << s2 << " are " << (h1 == h2 ? "EQUAL" : "DISTINCT") << endl;
    return 0;
}