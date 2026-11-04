// tags: segment tree lazy, range add, range min, coordinate compression, offline, greedy, math
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
// Idea: fix t = number of days using action 2 (one ration from every box). Boxes with c <= t are
// emptied by those days; each box with c > t needs its own action-1 day. So
//   answer = min over t >= 0 of f(t),   f(t) = t + #{boxes with c > t}.
// f only grows between consecutive box sizes, so an optimal t is 0 or a box size. Every f(t) is
// the cost of a real plan, so taking the min over EXTRA candidates (sizes of boxes not present
// right now) is harmless.
//
// Offline: candidates = {0} U {|X_i|}, compressed to indices 0..m-1 (sorted). Leaf i starts at
// f(t_i) = t_i (no boxes). A box of size c adds 1 to f(t) exactly for t < c, i.e. the prefix of
// candidates [0, idx(c)). So:
//   +c -> add +1 on [0, idx(c)),  -c -> add -1 on [0, idx(c)),  answer = global min.
// That is a lazy segment tree with range add + range min. Complexity: O(Q log Q).

/* Lazy Segment Tree (based on AtCoder Library's lazy_segtree), trimmed to what is used here */
// ranges are 0-indexed and half-open: [l, r)
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
struct LazySegTree {
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

    S all_prod() { return d[1]; }

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

// range add + range min
ll min_op(ll a, ll b) { return min(a, b); }
ll min_e() { return LLONG_MAX; } // only fills padding leaves, which never receive an add
ll add_mapping(ll f, ll x) { return x + f; } // adding f to every element shifts the min by f
ll add_composition(ll f, ll g) { return f + g; }
ll add_id() { return 0; }
using RangeAddMin = LazySegTree<ll, min_op, min_e, ll, add_mapping, add_composition, add_id>;

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int Q; cin >> Q;
    vi X(Q);
    for (int& x : X) cin >> x; // "+7" and "-2" parse as signed ints
    // candidate values of t: 0 plus every box size that ever appears, sorted and unique
    vi vals = {0};
    for (int x : X) vals.pb(abs(x));
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());
    // with no boxes, f(t) = t
    vector<ll> init(vals.begin(), vals.end());
    RangeAddMin st(init);
    rep(q, 0, Q) {
        int c = abs(X[q]);
        int i = lower_bound(vals.begin(), vals.end(), c) - vals.begin(); // index of c
        // candidates t < c are exactly the indices [0, i); i >= 1 because c >= 1 > 0 = vals[0]
        st.apply(0, i, X[q] > 0 ? 1 : -1);
        if (q) cout << ' ';
        cout << st.all_prod(); // min over all candidates t of f(t)
    }
    cout << '\n';
    return 0;
}
