// tags: segment tree lazy, rmq, implementation
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
int Q;
vector<int> X;

template<class t> class SegTreeLazy {
    vector<ll> *arr, st, lazy; 
    int n;
    void build(int u, int i, int j) {
        if (i == j) {
            st[u] = (*arr)[i];
            return;
        }
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        build(l, i, m);
        build(r, m + 1, j);
        st[u] = t::merge_op(st[l], st[r]);
    }
    void propagate(int u, int i, int j, ll x) {
        st[u] = t::range_op(st[u], i, j, x);
        if (i != j) { // If not a leaf, pass the update to children
            lazy[u * 2 + 1] = t::prop_op(lazy[u * 2 + 1], x);
            lazy[u * 2 + 2] = t::prop_op(lazy[u * 2 + 2], x);
        }
        lazy[u] = 0; // Reset lazy value for current node
    }
    
    ll query(int a, int b, int u, int i, int j) {
        if (j < a || b < i) return t::neutro;
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        if (a <= i && j <= b) return st[u];
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        ll x = query(a, b, l, i, m);
        ll y = query(a, b, r, m + 1, j);
        return t::merge_op(x, y);
    }
    
    void update(int a, int b, ll value, int u, int i, int j) {
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        if (a <= i && j <= b) {
            propagate(u, i, j, value);
        } else if (j < a || b < i) {
            return;
        } else {
            int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
            update(a, b, value, l, i, m);
            update(a, b, value, r, m + 1, j);
            st[u] = t::merge_op(st[l], st[r]);
        }
    }
public:
    SegTreeLazy(vector<ll>& v) {
        arr = &v;
        n = v.size();
        st.resize(n * 4 + 5);
        lazy.assign(n * 4 + 5, 0);
        build(0, 0, n - 1);
    }
    ll query(int a, int b) { return query(a, b, 0, 0, n - 1); }
    void update(int a, int b, ll value) { update(a, b, value, 0, 0, n - 1); }
};

struct RMinQ {
    static ll const neutro = LLONG_MAX;
    static ll merge_op(ll x, ll y) { return min(x, y); }
    static ll range_op(ll st_u, int a, int b, ll x) { return st_u + x; }
    static ll prop_op(ll child, ll x) { return child + x; }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> Q;
    X.resize(Q);
    rep(i,0,Q) cin >> X[i];
    set<int> S;
    for (int x : X) S.insert(abs(x)); // unique positive values
    S.insert(0); // 0 is the leftmost position
    S.insert(INT_MAX); // INT_MAX is the rightmost position
    umap<int,int> x2i;
    vector<ll> A(S.size());
    for (int x : S) {
        int i = x2i.size();
        x2i[x] = i;
        A[i] = x;
    }
    SegTreeLazy<RMinQ> st(A);
    bool first = true;
    for (int x : X) {
        int i = x2i[abs(x)];
        st.update(0, i-1, x < 0 ? -1 : 1);
        if (first) first = false;
        else cout << ' ';
        cout << st.query(0, A.size()-1);
    }
    cout << '\n';
    return 0;
}