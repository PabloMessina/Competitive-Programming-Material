// Tags: fenwick tree 2D
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
using namespace std;

#define FOR(i,a,b) for(int i=a; i<= b; ++i)
typedef long long int ll;

#define MAXN 1024

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


int N;
char buff[10];

int main() {
  int t;
  scanf("%d", &t);
  while(t--) {
    scanf("%d", &N);

    FenwickTree2D<ll> ft(N,N);

    while (true) {
      scanf("%s", buff);
      if (strcmp(buff, "SET") == 0) {
        int x, y; ll num;
        scanf("%d%d%lld", &x, &y, &num);
        ft.set(x, y, num);
      } else if (strcmp(buff, "SUM") == 0) {
        int x1, y1, x2, y2;
        scanf("%d%d%d%d", &x1,&y1,&x2,&y2);
        printf("%lld\n", ft.sum(x1,y1,x2,y2));
      } else
        break;
    }
  }
  return 0;
}


