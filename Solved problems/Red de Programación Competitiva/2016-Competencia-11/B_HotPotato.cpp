#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 50000

int N, Q;
int nums[MAXN];
vector<int> lows;
vector<vector<int>> g;

void bfs(int i) {
  queue<int> q;
  q.push(i);
  lows[i] = i;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) {
      if (lows[v] != -1)
        continue;
      lows[v] = i;
      q.push(v);
    }
  }
}

// ------------------
typedef vector<int>::iterator iter;

struct WaveTree {
  vector<vector<int>> r0; int n, s;

  void build(iter b, iter e, int l, int r, int u) {
    if (l == r)
      return;
    int m = (l+r) / 2;
    r0[u].reserve(e-b+1); r0[u].push_back(0);
    for (iter it = b; it != e; ++it)
      r0[u].push_back(r0[u].back() + (*it<=m));
    iter p = stable_partition(b, e, [=](int i){return i<=m;});
    build(b, p, l, m, u*2);
    build(p, e, m+1, r, u*2+1);
  }

  int q, w;
  int range(int a, int b, int l, int r, int u) {
    if (r < q or w < l)
      return 0;
    if (q <= l and r <= w)
      return b-a;
    int m = (l+r)/2, za = r0[u][a], zb = r0[u][b];
    return range(za, zb, l, m, u*2) + range(a-za, b-zb, m+1, r, u*2+1);
  }

  WaveTree(vector<int> arr, int sigma) {
    n = arr.size(); s = sigma;
    r0.resize(s*2);
    build(arr.begin(), arr.end(), 0, s-1, 1);
  }

  int quantile(int k, int a, int b) {
    if (k < 1 or k > b-a)
      return -1;
    int l = 0, r = s-1, u=1, m, za, zb;
    while (l != r) {
      m = (l+r)/2;
      za = r0[u][a]; zb = r0[u][b]; u*=2;
      if (k <= zb-za)
        a = za, b = zb, r = m;
      else
        k -= zb-za, a -= za, b -= zb,
        l = m+1, ++u;
    }
    return r;
  }

  int range(int x, int y, int a, int b) {
    if (y < x or b <= a)
      return 0;
    q = x; w = y;
    return range(a, b, 0, s-1, 1);
  }
};



int main() {
  while(scanf("%d%d", &N, &Q) == 2) {

    g.assign(N, vector<int>());
    rep(i,0,N-1) {
      scanf("%d", &nums[i]);
      nums[i]--;
      g[nums[i]].push_back(i);
    }

    lows.assign(N,-1);
    rep(i, 0, N-1) {
      if (lows[i] == -1)
        bfs(i);
    }

    WaveTree wt(lows, N);

    while (Q--) {
      int l, r; scanf("%d%d", &l,&r);
      --l; --r;

      int len = r-l+1;
      if (len == 1) {
        puts("1");
        continue;
      } 

      int x = wt.quantile(len/2, l, r+1);
      int c = wt.range(0,x,l,r+1);
      int f = abs(2*c - len);
      if (x > 0) {
        int c2 = wt.range(0, x-1,l,r+1);
        int f2 = abs(2*c2 - len);
        if (c2 > 0 && f2 <= f) {
          f = f2;
          x = wt.quantile(c2, l, r+1);
        }
      }
      if (f == len) {
        puts("1");
      } else {
        printf("%d\n", x+1);
      }

    }
  }
  return 0;
}