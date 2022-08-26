// tags: DP, bottom-up, binary search, segment tree, RMQ
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
const int MAXN = 3000;
int N;
ll S[MAXN], D[MAXN], F[MAXN+1];

template<class node> struct ST {
    vector<node> t; int n;
    ST() {}
    ST(vector<node> &arr) {
        n = arr.size();
        t.resize(n*2);
        copy(arr.begin(), arr.end(), t.begin() + n);
        for (int i = n-1; i > 0; --i)
            t[i] = node(t[i<<1], t[i<<1|1]);
    }
    // 0-indexed
    void set_point(int p, const node &value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = node(t[p], t[p^1]);
    }
    // inclusive exclusive, 0-indexed
    node query(int l, int r) {
        node ansl, ansr;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) ansl = node(ansl, t[l++]);
            if (r&1) ansr = node(t[--r], ansr);
        }
        return node(ansl, ansr);
    }
};

// Range Minimum Query
struct rminq {
    ll value;
    rminq() {value = LLONG_MAX;}
    rminq(int x) {value = x;}
    rminq(const rminq &a, const rminq &b) {
        value = min(a.value, b.value);
    }
};

vector<rminq> nodes[2][2][MAXN+1];
ST<rminq> st[2][2][MAXN+1];
ll dp[2][MAXN+1][MAXN+1];

ll add(ll a, ll b, ll c) {
    ll sum = a;
    if (a < LLONG_MAX) a += b + c;
    return a;
}

void update_node_and_st(int i, int j) {
    if (i > 0) {
        nodes[0][0][j][i-1].value = add(dp[0][i][j], D[i-1], S[i-1]);
        st[0][0][j].set_point(i-1, nodes[0][0][j][i-1]);
        
        nodes[0][1][j][i-1].value = add(dp[0][i][j], D[i-1], -S[i-1]);
        st[0][1][j].set_point(i-1, nodes[0][1][j][i-1]);
    }
    if (j < N) {
        nodes[1][0][i][j].value = add(dp[1][i][j], D[j], S[j]);
        st[1][0][i].set_point(j, nodes[1][0][i][j]);
        
        nodes[1][1][i][j].value = add(dp[1][i][j], D[j], -S[j]);
        st[1][1][i].set_point(j, nodes[1][1][i][j]);
    }
}

ll dp_bottom_up() {
    // init variables
    rep(i,0,2) rep(j,0,2) rep(k,0,N+1) {
        nodes[i][j][k] = vector<rminq>(N, rminq());
        st[i][j][k] = ST<rminq>(nodes[i][j][k]);
    }
    // base case: range size == 1
    rep(i,0,N+1) {
        dp[0][i][i] = F[i];
        dp[1][i][i] = F[i];
        update_node_and_st(i, i);
    }
    // general case: range size >= 2
    rep(len,1,N+1) {
        rep(i,0,N+1-len) {
            int j = i + len; // range = [i, j]
            // binary search
            int l = i, r = j;
            while (l < r) {
                int m = (l+r) >> 1;
                if (dp[1][i][m] >= dp[0][m+1][j]) r = m;
                else l = m+1;
            }
            int p = l;
            // dp(b=0, l=i, r=j)
            dp[0][i][j] = LLONG_MAX;
            ll ref = i > 0 ? S[i-1] : 0;
            if (i < p)  dp[0][i][j] = min(dp[0][i][j], st[0][0][j].query(i, p).value - ref);
            if (p < j) dp[0][i][j] = min(dp[0][i][j], st[1][0][i].query(p, j).value - ref);
            // dp(b=1, l=i, r=j)
            dp[1][i][j] = LLONG_MAX;
            if (j < N) {
                if (i < p) dp[1][i][j] = min(dp[1][i][j], st[0][1][j].query(i, p).value + S[j]);
                if (p < j) dp[1][i][j] = min(dp[1][i][j], st[1][1][i].query(p, j).value + S[j]);
            }
            update_node_and_st(i, j);
        }
    }

    return dp[0][0][N];
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    S[0] = 0;
    rep(i,1,N) { cin >> S[i]; S[i] += S[i-1]; }
    rep(i,0,N) cin >> D[i];
    rep(i,0,N+1) cin >> F[i];
    cout << dp_bottom_up() << '\n';
    return 0;
}