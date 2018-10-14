// tags: Rolling Hashing, strings, DP, graphs
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------

const int MAXLEN = 1e6;
const int MAXN = 1e4;

struct RH { // rolling hashing
    static const ll B = 33; // base
    static const ll P = 1e9 + 7; // prime
    static ll pow[MAXLEN];
    static void init() {
        pow[0] = 1;
        rep(i, 1, MAXLEN-1) pow[i] = (B * pow[i-1]) % P;
    }

    ll inline add(ll x, ll y) { return (x + y) % P; }
    ll inline mul(ll x, ll y) { return (x * y) % P; }
    
    vector<ll> hash;
    int len;
    RH(string& s) {
        len = s.size();
        hash.resize(len);
        hash[0] = s[0] - 'a';
        rep(i,1,len-1) hash[i] = add(mul(hash[i-1], B),s[i] - 'a');
    }

    ll get_hash(int i, int j) {
        if (i == 0) return hash[j];
        return add(hash[j], P - mul(hash[i-1], pow[j - i + 1]));
    }

    ll get_hash() {
        return hash[len-1];
    }

    bool operator<(const RH& o) { return len < o.len; }
};
ll RH::pow[MAXLEN];

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
            while (j < n and rhs[j].len == rhs[i].len) j++;
            if (j == n) break;
            rep(k,j,n-1) {
                RH& rhk = rhs[k];
                int d = rhk.len - rhi.len;
                rep(x,0,d) if (rhk.get_hash(x, x + rhi.len - 1) == rhi.get_hash()) {
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