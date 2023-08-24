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
int N;
const int MAXN = 1e5 + 5;
ll D[MAXN], V[MAXN], T[MAXN];
ll DP[MAXN];

template<class node> struct ST {
    vector<node> t; int n;
    ST(const vector<node> &arr) {
        n = arr.size();
        t.resize(n*2);
        copy(arr.begin(), arr.end(), t.begin() + n);
        for (int i = n-1; i > 0; --i)
            t[i] = node(t[i<<1], t[i<<1|1]);
    }
    ST(int n) : ST(vector<node>(n)) { }
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

struct node { // Range Maximum Query
    ll value;
    node() { value = LLONG_MIN; }
    node(ll x) {value = x;}
    node(const node &a, const node &b) {
        value = max(a.value, b.value);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N;
    set<ll> ds;
    umap<ll,int> d2i;
    rep(i,0,N) {
        cin >> D[i] >> V[i] >> T[i];
        ds.insert(D[i]);
        ds.insert(D[i] - T[i]);
    }
    int i = 0;
    for (ll d : ds) {
        d2i[d] = i;
        ++i;
    }
    int M = ds.size();
    ST<node> st(M);
    DP[0] = V[0];
    st.set_point(d2i[D[0]], node(DP[0]));
    rep(i,1,N) {
        ll tmp = st.query(d2i[D[i] - T[i]], d2i[D[i]] + 1).value;
        DP[i] = max(tmp, 0LL) + V[i];
        st.set_point(d2i[D[i]], node(DP[i]));
    }
    cout << st.query(0, M).value << '\n';
    return 0;
}