struct BIT { // BIT = binary indexed tree (a.k.a. Fenwick Tree)
    vector<int> bit;
    BIT(int n) { bit.assign(n+1, 0); }
    // prefix sum query (sum in range 1 .. k)
    int psq(int k) {
        int sum = 0;
        for (; k; k -= (k & -k)) sum += bit[k];
        return sum;
    }
    // range sum query (sum in range a .. b)
    int rsq(int a, int b) {
        return psq(b) - psq(a-1);
    }
    // increment k'th value by v (and propagate)
    void add(int k, int v) {
        for (; k < bit.size(); k += (k & -k)) bit[k] += v;
    }
};