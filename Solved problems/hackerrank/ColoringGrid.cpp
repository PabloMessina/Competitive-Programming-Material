// ToDo: finish this
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
// -------------------------------
const ll MOD = 1000000007;

ll mul(ll x, ll y) { return (x*y) % MOD; }
ll add(ll x, ll y) { return (x+y) % MOD; }

struct DP {
    int n, m, k;
    vector<umap<int,int>> memo;
    vector<int> _hash;
    vector<bool> _used_colors;
    int _used_color_count;
    DP(int n, int m, int k) : n(n), m(m), k(k) {
        memo.resize(n*m);
        _hash.resize(m);
    }
    void decode(int hash) {
        _used_colors.assign(m, false);
        _used_color_count = 0;
        rep(i,0,m-1) {
            int color = (hash >> 3 * i) & 7;
            _hash[i] = color;
            if (!_used_colors[color]) {
                _used_colors[color] = true;
                _used_color_count++;
            }
        }
    }
    int encode(int i, int color) {
        static vector<int> old2new, hash_tmp;
        old2new.assign(m+1, -1);
        hash_tmp.copy(_hash);
        hash_tmp[i] = color;
        int id = 0;
        for (int x : hash_tmp) if (old2new[x] == -1) old2new[x] = id++;
        int hash = 0;
        rep(i,0,m-1) hash |= (hash_tmp[i] << 3*i);
        return hash;
    }
    ll operator()(int r, int c, int hash) {
        // int idx = get_idx(hash);
        auto& dict = memo[r * n + c];
        auto it = dict.find(hash);
        if (it != dict.end()) return it->second;
        
        if (r == n) return 1;
        assert (r < n and c < m);
        decode(hash);
        int next_r, next_c, hash2;
        if (c == n-1) next_r = r+1, next_c = 0;
        else next_r = r, next_c = c+1;        
        if (r == 0) {
            if (c == 0) {
                hash2 = encode(c, 0);
                return ans = mul(n*m, (*this)(next_r, next_c, hash2));
            } else {
                ll tmp = 0;
                rep(color,0,_used_color_count-1) {
                    hash2 = encode(c, color);
                    tmp = add(tmp, (*this)(next_r, next_c, hash2));
                }
                hash2 = encode(c, _used_color_count);
                tmp = add(tmp, mul(n*m - _used_color_count, (*this)(next_r, next_c, hash2)));
            }
            if (c == m-1) {
            return 8ll * (*this)(r )

            }
        }

    }

};

ll memo_ways[9][9][65];
ll ways(int n, int m, int k) {
    ll& ans = memo_ways[n][m][k];
    if (ans != -1) return ans;
}

vector<ll>& get_poly_coefs(int n, int m) {
    static bool solved[9][9] = {0};
    static vector<ll> cache[9][9];
    if (solved[n][m]) return cache[n][m];

    auto& ans = cache[n][m];
    int d = n*m;
    ans.resize(d+1);
    rep(k,0,d) ans[k] = ways(n, m, k);

    solved[n][m] = true;
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N, M; ll K;
        cin >> N >> M >> K;
        cout << calc(get_poly_coefs(N, M), K) << '\n';
    }
    return 0;
}