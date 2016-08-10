// TODO: it's wrong, yields TLE
#include <cstdio>
#include <cmath>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef long long int ll;

const ll M = 5318008;
ll dp[5001];
ll aux[5001];

inline void swap(int x, int y) {
  int tmp = x; x = y; y = tmp;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T--) {
    int n, x1, x2, y1, y2;
    scanf("%d", &n);
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
    x1--,y1--,x2--,y2--;
    if (abs(x2-x1) < abs(y2-y1))
      swap(x1, y1), swap(x2, y2);
    if (x1 > x2)
      swap(x1, x2), swap(y1, y2);
    memset(dp, 0, sizeof(dp[0]) * n);
    dp[y1] = 1;
    rep (i, x1, x2-1) {
      memset(aux, 0, sizeof(aux[0]) * n);
      rep (j, 0, n-1) {
        if (j > 0) aux[j-1] = (aux[j-1] + dp[j]) % M;
        aux[j] = (aux[j] + dp[j]) % M;
        if (j < n-1) aux[j+1] = (aux[j+1] + dp[j]) % M;
      }
      memcpy(dp, aux, sizeof(dp[0]) * n);
    }
    printf("%lld\n", dp[y2] % M);
  }
  return 0;
}