template<typename T> struct FT { // fenwick tree, 1-indexed: positions 1..n. e.g. FT<ll> ft(n);
    vector<T> t;
    FT(int n) : t(n+1, 0) {}
    T query(int i) { // sum in range [1 .. i], query(0) = 0
        T ans = 0;
        for (; i > 0; i -= (i & -i)) ans += t[i];
        return ans;
    }
    T query(int i, int j) { return query(j) - query(i-1); } // sum in range [i .. j]
    void update(int i, T v) { // increment i'th value by v (and propagate)
        for (; i < (int)t.size(); i += (i & -i)) t[i] += v;
    }
    // smallest i with query(i) >= k (k >= 1), or n+1 if query(n) < k. O(log n).
    // Needs every value >= 0, so prefix sums never decrease. Main use: values are counts of
    // compressed values -> lower_bound(k) is the slot of the k-th smallest element of a
    // multiset with insertions and deletions. (Binary search over query() also works, but
    // costs O(log^2 n).) Binary lifting: t[pos + 2^b] covers exactly the next 2^b slots
    // after pos, so walk down the powers of 2, skipping whole blocks whose sum is still < k
    int lower_bound(T k) {
        int n = (int)t.size() - 1, pos = 0;
        for (int pw = 1 << __lg(max(n, 1)); pw > 0; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < k) { pos += pw; k -= t[pos]; }
        return pos + 1;
    }
    // range update + point query mode: add v to every value in [i .. j],
    // then query(i) is the value at i. Don't mix with range sums above.
    void update(int i, int j, T v) { update(i, v); update(j + 1, -v); }
};
