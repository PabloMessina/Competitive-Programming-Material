template<typename T> struct FT2D {
    vector<vector<T>> ft;
    int R, C;
    FT2D(int _R, int _C) : R(_R+1), C(_C+1) {
        ft.assign(R, vector<T>(C, 0));
    }
    void add(int r, int c, T val) {
        for (int i = r; i < R; i += (i&-i))
            for (int j = c; j < C; j += (j&-j))
                ft[i][j] += val;
    }
    // sum[(1, 1), (r, c)]
    T sum(int r, int c) {
        T res = 0;
        for (int i = r; i; i -= (i&-i))
            for (int j = c; j; j -= (j&-j))
                res += ft[i][j];
        return res;
    }
    // sum[(r1, c1), (r2, c2)]
    T sum(int r1, int c1, int r2, int c2) {
        return sum(r2, c2) - sum(r1-1, c2) - sum(r2, c1-1) + sum(r1-1, c1-1);
    }
    // get value at cell (r,c)
    T get(int r, int c) {
        return sum(r, c, r, c);
    }
    // set value to cell (r,c)
    void set(int r, int c, int value) {
        add(r, c, -get(r, c) + value);
    }
};