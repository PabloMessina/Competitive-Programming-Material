template<class t> class SegTreeLazy {
    vector<ll> *arr, st, lazy; 
    int n;
    // Build the segment tree from input array (u: node, [i,j]: range)
    void build(int u, int i, int j) {
        if (i == j) { // Leaf node: represents a single element in the array
            st[u] = (*arr)[i];
            return;
        }
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        build(l, i, m);
        build(r, m + 1, j);
        // Combine results from children using the template's merge operation
        st[u] = t::merge_op(st[l], st[r]);
    }
    // Apply pending updates to a node and push them to children.
    void propagate(int u, int i, int j, ll x) {
        // Update the current node's value based on the range size (i to j)
        st[u] = t::range_op(st[u], i, j, x);
        if (i != j) { // If not a leaf, pass the update to children
            lazy[u * 2 + 1] = t::prop_op(lazy[u * 2 + 1], x);
            lazy[u * 2 + 2] = t::prop_op(lazy[u * 2 + 2], x);
        }
        lazy[u] = 0; // Reset lazy value for current node
    }
    // Internal query function.
    ll query(int a, int b, int u, int i, int j) {
        // 1. Out of bounds
        if (j < a || b < i) return t::neutro;
        // 2. Handle pending updates before processing
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        // 3. Current node range is fully within target range
        if (a <= i && j <= b) return st[u];
        // 4. Partial overlap: check both children
        int m = (i + j) / 2, l = u * 2 + 1, r = u * 2 + 2;
        ll x = query(a, b, l, i, m);
        ll y = query(a, b, r, m + 1, j);
        return t::merge_op(x, y);
    }
    // Internal update function.
    void update(int a, int b, ll value, int u, int i, int j) {
        // Handle pending updates first
        if (lazy[u]) propagate(u, i, j, lazy[u]);
        if (a <= i && j <= b) {
            // Current node range is fully within target: apply update here
            propagate(u, i, j, value);
        } else if (j < a || b < i) {
            // Out of bounds: do nothing
            return;
        } else {
            // Partial overlap: update children and then re-merge
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
    // Public API: Uses 0-indexed ranges [a, b] inclusive
    ll query(int a, int b) { return query(a, b, 0, 0, n - 1); }
    void update(int a, int b, ll value) { update(a, b, value, 0, 0, n - 1); }
};

// Range Sum Query
struct RSQ {
    static ll const neutro = 0;
    static ll merge_op(ll x, ll y) { return x + y; }
    static ll range_op(ll st_u, int i, int j, ll x) { return st_u + (ll)(j - i + 1) * x; }
    static ll prop_op(ll child, ll x) { return child + x; }
};
// Range Minimum Query
struct RMinQ {
    static ll const neutro = LLONG_MAX;
    static ll merge_op(ll x, ll y) { return min(x, y); }
    static ll range_op(ll st_u, int a, int b, ll x) { return st_u + x; }
    static ll prop_op(ll child, ll x) { return child + x; }
};

int main() {
    // Example: Initial array A = [18, 17, 13, 19, 15, 11, 20]
    vector<ll> A = { 18, 17, 13, 19, 15, 11, 20 };
    SegTreeLazy<RSQ> stl(A);
    // Update range: indices 1 to 5 inclusive, add 100 to each.
    // Resulting range [1,5] becomes: [117, 113, 119, 115, 111]
    stl.update(1, 5, 100);
    // Query sum of range: indices 1 to 3 inclusive.
    // Logic: A[1] + A[2] + A[3] = 117 + 113 + 119 = 349
    cout << "Sum [1, 3]: " << stl.query(1, 3) << endl; 
    return 0;
}