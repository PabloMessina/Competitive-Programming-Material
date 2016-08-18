#include <cstdio>
#include <cmath>
using namespace std;

int main() {
  int m, n;
  scanf("%d%d",&m,&n);
  double ans = 0;
  for (int z = 1; z <= m; ++z) {
    double a = z / (double)m;
    double b = (z-1) / (double)m;
    ans += z * (pow(a,n) - pow(b,n));
  }
  printf("%lf\n", ans);
  return 0;
}