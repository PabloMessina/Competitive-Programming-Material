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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
const int MAXLEN = 500000 + 5;
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
    static ull shift_left(ull h, int k) {
        ull ans = 0;
        rep(a,0,2) {
            ull hh = (h >> (32 * a)) & ((1ull << 32) - 1);
            hh = mul(hh, pow[a][k], a);
            ans |= hh << (32 * a);
        }
        return ans;
    }
    static ull add(ull x, ull y) {
        ull ans = 0;
        rep(a,0,2) {
            ull xx = (x >> (32 * a)) & ((1ull << 32) - 1);
            ull yy = (y >> (32 * a)) & ((1ull << 32) - 1);            
            ans |= add(xx, yy, a) << (32 * a);
        }
        return ans;
    }
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
        if (i > j) return 0;
        if (i == 0) return h[a][j];
        return add(h[a][j], P[a] - mul(h[a][i-1], pow[a][j-i+1], a), a);
    }
    ull hash(int i, int j) { return hash(i,j,1) << 32 | hash(i,j,0); }
    ull hash() { return hash(0, len-1); }
};
const ull RH::P[2] = {(ull)1e9+21, (ull)1e9+9};
ull RH::pow[2][MAXLEN];

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    RH::init();
    int T; cin >> T;
    rep(_t,1,T+1) {
        int n, k; cin >> n >> k;
        vector<int> A(n), B(n);
        rep(i,0,n) cin >> A[i];
        rep(i,0,n) cin >> B[i];
        int offset;
        bool equal = false;
        ull hash_a = RH(A).hash();
        auto rh_b = RH(B);
        bool yes = false;
        rep(i,0,n) {
            ull hash_b = rh_b.add(rh_b.shift_left(rh_b.hash(i, n-1), i), rh_b.hash(0, i-1));
            if (hash_a == hash_b) {
                if (k == 0) {
                    if (i == 0) {
                        yes = true; break;
                    }
                } else if (k == 1) {
                    if (i != 0) {
                        yes = true; break;
                    }
                } else {
                    if ((k % 2) == 0) {
                        if (i == 0) {
                            yes = true; break;
                        } else if (n > 2) {
                            yes = true; break;
                        }
                    } else {
                        if (i > 0) {
                            yes = true; break;
                        } else if (n > 2) {
                            yes = true; break;
                        }
                    }
                }
            }
        }
        cout << "Case #" << _t << ": ";
        if (yes) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}