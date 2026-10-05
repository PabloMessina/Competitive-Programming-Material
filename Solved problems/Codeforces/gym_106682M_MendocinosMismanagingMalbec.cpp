// tags: segment tree, lazy propagation, range assignment, binary search on segment tree, min_left
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
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

/* ========================================================================= */
/* Lazy Segment Tree (based on AtCoder Library's lazy_segtree, needs C++17)  */
/* ========================================================================= */
// Source: https://github.com/atcoder/ac-library/blob/master/atcoder/lazysegtree.hpp
// Docs:   https://github.com/atcoder/ac-library/blob/master/document_en/lazysegtree.md
//
// Supports, all in O(log n):
//   - apply an update f to every element of a range
//   - query the "sum" (any associative op) of a range
//   - binary search on the tree (max_right / min_left)
//
// ALL RANGES ARE 0-INDEXED AND HALF-OPEN: [l, r)
//
// You must define (see examples below):
//   S                  type stored in each node (often a struct, e.g. {sum, len})
//   S op(S a, S b)     combine two adjacent nodes (must be associative)
//   S e()              identity of op: op(e(), x) == op(x, e()) == x
//   F                  type of an update
//   S mapping(F f, S x)        apply update f to a node x
//   F composition(F f, F g)    the update "first g, then f" (f is the NEWER one)
//   F id()             the "do nothing" update
//
// Tip: if the update depends on the segment length (e.g. range add + range sum),
// store the length inside S, since mapping() doesn't receive the range.
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
struct LazySegTree {
    LazySegTree(int n) : LazySegTree(vector<S>(n, e())) {}
    LazySegTree(const vector<S>& v) : _n(v.size()) {
        log = 0;
        while ((1 << log) < _n) log++;
        size = 1 << log; // smallest power of 2 >= n
        d.assign(2 * size, e());
        lz.assign(size, id());
        // node k has children 2k and 2k+1; leaves are size..size+n-1
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) update(i);
    }

    // a[p] = x
    void set(int p, S x) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // returns a[p]
    S get(int p) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    // returns op(a[l], ..., a[r-1]), or e() if l == r
    S prod(int l, int r) {
        if (l == r) return e();
        l += size; r += size;
        // push pending updates on the paths from the root to l and r-1
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sml = e(), smr = e(); // left and right accumulators (op may not be commutative)
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1; r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    // a[p] = f(a[p])
    void apply(int p, F f) {
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    // a[i] = f(a[i]) for all i in [l, r)
    void apply(int l, int r, F f) {
        if (l == r) return;
        l += size; r += size;
        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1; r >>= 1;
            }
            l = l2; r = r2;
        }
        // recompute the ancestors of the touched nodes
        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    // BINARY SEARCH TO THE RIGHT. Requires g(e()) == true.
    // Returns the largest r such that g(op(a[l], ..., a[r-1])) is true,
    // assuming g is monotone (true, true, ..., true, false, false, ...).
    // Returns n if g holds all the way to the end.
    template <class G> int max_right(int l, G g) {
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = 2 * l;
                    if (g(op(sm, d[l]))) { sm = op(sm, d[l]); l++; }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    // BINARY SEARCH TO THE LEFT. Requires g(e()) == true.
    // Returns the smallest l such that g(op(a[l], ..., a[r-1])) is true,
    // assuming g is monotone as l decreases.
    // Returns 0 if g holds all the way to the beginning.
    template <class G> int min_left(int r, G g) {
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = 2 * r + 1;
                    if (g(op(d[r], sm))) { sm = op(d[r], sm); r--; }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

private:
    int _n, size, log;
    vector<S> d;  // d[k]: value of node k (already includes its own pending update)
    vector<F> lz; // lz[k]: update pending to be pushed to k's children (internal nodes only)

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

/* ---------------------------------------------- */
/* Problem-specific node and updates              */
/* ---------------------------------------------- */
// Each node stores how much malbec its barrels hold and their total capacity.
// Capacity never changes, so "fill completely" can be applied to a whole node in O(1).
struct Node { ll fill, cap; };
Node node_op(Node a, Node b) { return {a.fill + b.fill, a.cap + b.cap}; }
Node node_e() { return {0, 0}; }

// Updates are range assignments: empty every barrel, or fill every barrel.
enum Upd { NONE, EMPTY, FULL };
Node upd_mapping(Upd f, Node x) {
    if (f == EMPTY) return {0, x.cap};
    if (f == FULL) return {x.cap, x.cap};
    return x;
}
Upd upd_composition(Upd f, Upd g) { return f == NONE ? g : f; } // newer one wins
Upd upd_id() { return NONE; }

using SegTree = LazySegTree<Node, node_op, node_e, Upd, upd_mapping, upd_composition, upd_id>;

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int N, M; cin >> N >> M;
    vector<Node> init(N);
    rep(i, 0, N) {
        ll a; cin >> a;
        init[i] = {0, a}; // all barrels start empty
    }
    SegTree st(init);
    while (M--) {
        int t; cin >> t;
        if (t == 1) {
            int B; ll V; cin >> B >> V;
            int b = B - 1; // 0-indexed
            // Malbec flows from b towards barrel 0. Find the smallest l such that
            // the free space in barrels [l, b] is <= V: all of them get filled.
            // Free space only grows as l decreases, so the condition is monotone.
            int l = st.min_left(b + 1, [&](Node x) { return x.cap - x.fill <= V; });
            Node seg = st.prod(l, b + 1);
            ll leftover = V - (seg.cap - seg.fill);
            st.apply(l, b + 1, FULL);
            // The leftover goes into barrel l-1. By the choice of l, it has more free
            // space than the leftover, so it ends up partially filled.
            // If l == 0, the leftover falls to the floor.
            if (l > 0 && leftover > 0) {
                Node x = st.get(l - 1);
                st.set(l - 1, {x.fill + leftover, x.cap});
            }
        } else {
            int L, R; cin >> L >> R;
            cout << st.prod(L - 1, R).fill << '\n';
            st.apply(L - 1, R, EMPTY);
        }
    }
    return 0;
}
