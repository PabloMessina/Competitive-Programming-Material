// tags: Rolling Hashing, strings, DP, graphs
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ull;
// -------------------------------

const int MAXLEN = 1e6;
const int MAXN = 1e4;

struct RH { // rolling hashing
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
    RH(string& s) {
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
    
    bool operator<(const RH& o) const { return len < o.len; }
};
ull RH::pow[MAXLEN]; // necessary for the code to compile

vector<vector<int>> g;
int memo[MAXN];
int dp(int i) {
    int& ans = memo[i];
    if (ans != -1) return ans;
    int tmp = 0;
    for (int j : g[i]) tmp = max(tmp, dp(j));
    return ans = tmp + 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    RH::init();
    vector<RH> rhs;
    rhs.reserve(MAXN);
    g.reserve(MAXN);
    int n;
    while ((cin >> n) and n) {
        rhs.clear();
        rep(i,0,n-1) {
            string s; cin >> s;
            rhs.emplace_back(s);
        }
        sort(rhs.begin(), rhs.end());
        g.assign(n, vector<int>());
        int j = 1;
        rep(i,0,n-2) {
            RH& rhi = rhs[i];
            ull hash_i = rhi.hash();
            while (j < n and rhs[j].len == rhs[i].len) j++;
            if (j == n) break;
            rep(k,j,n-1) {
                RH& rhk = rhs[k];
                int d = rhk.len - rhi.len;
                rep(x,0,d) if (rhk.hash(x, x + rhi.len - 1) == hash_i) {
                    g[i].push_back(k);
                    break;
                }
            }
        }
        int ans = 0;
        memset(memo, -1, sizeof(int) * n);
        rep(i,0,n-1) ans = max(ans, dp(i));
        cout << ans << endl;
    }
    return 0;
}