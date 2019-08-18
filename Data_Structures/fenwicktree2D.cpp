struct BIT2D { // BIT = binary indexed tree (a.k.a. Fenwick Tree)
    vector<int> bit;
    vector<int> values; // optional: to keep track of actual values
    int R, C;
    BIT2D(int _R, int _C) : R(_R), C(_C) {
        bit.assign(R * C, 0);
        values.assign(R * C, 0);
    }
    void add(int r, int c, int value) {
        for (int i = r; i < R; i += (i&-i))
            for (int j = c; j < C; j += (j&-j))
                bit[i * C + j] += value;
        values[r*C+c] += value;
    }
    // sum[(1, 1), (r, c)]
    int sum(int r, int c) {
        int res = 0;
        for (int i = r; i; i -= (i&-i))
            for (int j = c; j; j -= (j&-j))
                res += bit[i * C + j];
        return res;
    }
    // sum[(r1, c1), (r2, c2)]
    int sum(int r1, int c1, int r2, int c2) {
        return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
    }
    int get(int r, int c) { // get value at cell (r,c)
        return values[r * C + c];
        // return sum(r, c, r, c); // or using sum
    }
    int set(int r, int c, int value) { // set value to cell (r,c)
        add(r, c, -get(r, c) + value);
    }
};