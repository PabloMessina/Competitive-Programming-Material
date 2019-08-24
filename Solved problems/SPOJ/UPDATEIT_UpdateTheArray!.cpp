#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

template<class t> class SegTreeLazy {
    vector<ll> *arr, st, lazy; int n;

    void build(int u, int i, int j) {
        if (i == j) {
            st[u] = (*arr)[i];
            return;
        }
        int m = (i+j)/2, l = u*2+1, r = u*2+2;
        build(l, i, m);
        build(r, m+1, j);
        st[u] = t::merge_op(st[l], st[r]);
    }

    void propagate(int u, int i, int j, ll x) {
        st[u] += t::range_op(i, j, x);
        if (i != j) {
            lazy[u*2+1] += x;
            lazy[u*2+2] += x;
        }
        lazy[u] = 0;
    }

    ll query(int a, int b, int u, int i, int j) {
        if (j < a or b < i) return t::neutro;
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        if (a <= i and j <= b) return st[u];
        int m = (i+j)/2, l = u*2+1, r = u*2+2;
        ll x = query(a, b, l, i, m);
        ll y = query(a, b, r, m+1, j);
        return t::merge_op(x, y);
    }

    void update(int a, int b, ll value, int u, int i, int j) {
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        if (a <= i and j <= b) propagate(u, i, j, value);
        else if (j < a or b < i) return; else {
            int m = (i+j)/2, l = u*2+1, r = u*2+2;
            update(a, b, value, l, i, m);
            update(a, b, value, r, m+1, j);
            st[u] = t::merge_op(st[l], st[r]);
        }
    }

public:
    SegTreeLazy(vector<ll>& v) {
        arr = &v;
        n = v.size();
        st.resize(n*4+5);
        lazy.assign(n*4+5, 0);
        build(0, 0, n-1);
    }

    ll query(int a, int b) {
        return query(a, b, 0, 0, n-1);
    }

    void update(int a, int b, ll value) {
        update(a, b, value, 0, 0, n-1);
    }
};

struct RSQ {
    static ll const neutro = 0;
    static ll merge_op(ll x, ll y) { return x + y; }
    static ll range_op(int i, int j, ll x) { return (j - i + 1) * x; }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    vector<ll> arr;
    while (T--) {
        int n, u; cin >> n >> u;
        arr.assign(n, 0);
        SegTreeLazy<RSQ> lst(arr);
        while (u--) {
            int l, r, val; cin >> l >> r >> val;
            lst.update(l, r, val);
        }
        int q; cin >> q;
        while (q--) {
            int i; cin >> i;
            cout << lst.query(i, i) << '\n';
        }
    }
    return 0;
}