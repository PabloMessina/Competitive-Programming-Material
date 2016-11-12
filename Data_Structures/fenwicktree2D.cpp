template<class T> class FenwickTree2D {
  vector<vector<T> > t;
  int n, m;
    
public:
  FenwickTree2D() {}

  FenwickTree2D(int n, int m) {
    t.assign(n, vector<T>(m, 0));
    this->n = n; this->m = m;
  }

  void add(int r, int c, T value) {
    for (int i = r; i < n; i |= i + 1)
      for (int j = c; j < m; j |= j + 1)
        t[i][j] += value;
  }

  // sum[(0, 0), (r, c)]
  T sum(int r, int c) {
    T res = 0;
    for (int i = r; i >= 0; i = (i & (i + 1)) - 1)
      for (int j = c; j >= 0; j = (j & (j + 1)) - 1)
        res += t[i][j];
    return res;
  }

  // sum[(r1, c1), (r2, c2)]
  T sum(int r1, int c1, int r2, int c2) {
    return sum(r2, c2) - sum(r1 - 1, c2) - sum(r2, c1 - 1) + sum(r1 - 1, c1 - 1);
  }

  T get(int r, int c) {
    return sum(r, c, r, c);
  }

  void set(int r, int c, T value) {
    add(r, c, -get(r, c) + value);
  }
};