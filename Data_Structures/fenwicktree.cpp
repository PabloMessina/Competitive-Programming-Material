struct FenwickTree {
    vector<int> ft;
    FenwickTree(int n) { ft.assign(n+1, 0); }
    // prefix sum query (sum in range 1 .. k)
    int psq(int k) {
        int sum = 0;
        for (; k; k -= (k & -k)) sum += ft[k];
        return sum;
    }
    // range sum query (sum in range a .. b)
    int rsq(int a, int b) {
        return psq(b) - psq(a-1);
    }
    // increment k'th value by v (and propagate)
    void add(int k, int v) {
        for (; k < ft.size(); k += (k & -k)) ft[k] += v;
    }
    // increment range [i ... j] with v (and propagate)
    void range_add(int i, int j, int v) {
        add(i, v); add(j+1, -v);
    }
};