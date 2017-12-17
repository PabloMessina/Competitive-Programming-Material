struct FenwickTree2D {
    vector<vector<int>> ft;
    int n, m;

    FenwickTree2D(int n, int m) : n(n), m(m) {
        ft.assign(n, vector<T>(m, 0));
    }

    void add(int r, int c, int value) {
        for (int i = r; i < n; i += (i&-i))
            for (int j = c; j < m; j += (j&-j))
                ft[i][j] += value;
    }

    // sum[(1, 1), (r, c)]
    int sum(int r, int c) {
        int res = 0;
        for (int i = r; i; i -= (i&-i))
            for (int j = c; j; j -= (j&-j))
                res += ft[i][j];
        return res;
    }

    // sum[(r1, c1), (r2, c2)]
    int sum(int r1, int c1, int r2, int c2) {
        return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
    }

    int get(int r, int c) {
        return sum(r, c, r, c);
    }

    int set(int r, int c, int value) {
        add(r, c, -get(r, c) + value);
    }
};