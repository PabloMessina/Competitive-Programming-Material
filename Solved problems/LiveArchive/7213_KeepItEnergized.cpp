#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 100000
#define INF 1000000007

int N, M;
int accE[MAXN+1];
int level[MAXN+1];
int shopIndex[MAXN+1];
int strength[MAXN+1];
int cost[MAXN+1];
int mincost[MAXN+1];
int lastShopPerLevel[MAXN+1];

int energyToArrive(int i, int j) {
  int li = level[shopIndex[i]];
  int lj = level[shopIndex[j]];
  int a = (li > 0 ? accE[li-1] : 0);
  int b = (lj > 0 ? accE[lj-1] : 0);
  return b - a;
}

int furthestReachable(int from) {
  int i = from, j = M;
  int s = strength[shopIndex[from]];
  while (i < j) {
    int m = (i + j) / 2;
    int e = energyToArrive(from, m);
    if (e > s) // unreachable
      j = m;
    else // reachable
      i = m + 1;
  }
  if (energyToArrive(from, i) > s) // first unreachable found
    return i - 1;
  else // all are reachable
    return M;
}

/* segment tree */
int st[(MAXN + 1) * 4 + 5];
int stindex[MAXN + 1];
int left(int node) {
  return node << 1;
}
int right (int node) {
  return (node << 1) + 1;
}
void build_st(int node, int l, int r) {
  if (l == r) {
    st[node] = l;
    stindex[l] = node;
  } else {
    build_st(left(node), l, (l + r) / 2);
    build_st(right(node), (l + r)/2 + 1, r);
    int i1 = st[left(node)];
    int i2 = st[right(node)];
    st[node] = (mincost[i1] < mincost[i2]) ? i1 : i2;
  }
}
void update_point(int i, int new_value) {
  mincost[i] = new_value;
  int node = stindex[i];
  while ((node >>= 1) > 0) {
    int i1 = st[left(node)];
    int i2 = st[right(node)];
    st[node] = (mincost[i1] < mincost[i2]) ? i1 : i2;
  }
}
int rmq (int node, int l, int r, int i, int j) {
  if (i > j || l > j || r < i) return -1;
  if (l >= i && r <= j) return st[node];
  int i1 = rmq(left(node),l,(l+r)/2,i,j);
  int i2 = rmq(right(node),(l+r)/2+1,r,i,j);
  if (i1 == -1) return i2;
  if (i2 == -1) return i1;
  return (mincost[i1] < mincost[i2]) ? i1 : i2;
}

bool cmp(int i, int j) {
  return level[i] < level[j];
}

int main() {
  begin:
  while (scanf("%d %d", &N, &M) == 2) {
    FOR(i,0,N-1) {
      scanf("%d", &accE[i]);
      if (i > 0) accE[i] += accE[i-1];
    }
    bool canStart = false;
    FOR(i,0,M-1) {
      scanf("%d %d %d", &level[i], &strength[i], &cost[i]);
      level[i]--;
      mincost[i] = INF;
      shopIndex[i] = i;
      if (level[i] == 0) canStart = true;
    }
    if (!canStart) {
      puts("-1");
      goto begin;
    }
    sort(shopIndex, shopIndex + M, cmp);
    memset(lastShopPerLevel, -1, sizeof lastShopPerLevel);
    FOR(i, 0, M - 1) {
      int si = shopIndex[i];
      int l = level[si];
      lastShopPerLevel[l] = max(lastShopPerLevel[l], i);
    }

    level[M] = N;
    shopIndex[M] = M;
    mincost[M] = 0;
    // dp
    build_st(1, 0, M);
    for (int i = M-1; i >= 0; --i) {

      int shop_i = shopIndex[i];
      int ls_i = lastShopPerLevel[level[shop_i]];
      int r = furthestReachable(i);

      int min_i = -1, min_c = INF;

      if (ls_i <= r) {
        int min_i1 = rmq(1, 0, M, i + 1, ls_i);
        int min_i2 = rmq(1, 0, M, ls_i + 1, r);
        if (min_i1 != -1 && min_c > mincost[min_i1]) {
          min_i = min_i1;
          min_c = mincost[min_i];
        }        
        if (min_i2 != -1 && min_c > mincost[min_i2] + cost[shop_i]) {
          min_i = min_i2;
          min_c = mincost[min_i] + cost[shop_i];
        }
      } else {
        int min_i = rmq(1, 0, M, i + 1, r);
        if (min_i != -1 && min_c > mincost[min_i])
          min_c = mincost[min_i];
      }
      if (min_c < INF)
        update_point(i, min_c);
    }
    // answer
    if (mincost[0] < INF)
      printf("%d\n", mincost[0]);
    else
      puts("-1");
  }
  return 0;
}