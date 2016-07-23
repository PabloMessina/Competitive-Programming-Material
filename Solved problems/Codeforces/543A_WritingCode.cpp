/*
* Algorithms used:
*  DP (bottom-up) + memory optimization
*/
#include <cstdio>
#include <cstring>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;++i)
typedef long long int ll;

int main() {
  int n,m,b,mod;
  scanf("%d %d %d %d",&n,&m,&b,&mod);
  int a;
  ll ways[m+1][b+1];
  memset(ways, 0, sizeof ways);
  // last programmer (base case)
  scanf("%d",&a);
  FOR(l,0,m) FOR(e,0,b) {
    if (l*a <= e) ways[l][e] = 1 % mod;
  }
  // other programmers
  FOR(p,1,n-1) {
    scanf("%d",&a);
    FOR(l,1,m) FOR(e,a,b) {
      if ((ways[l][e] += ways[l-1][e - a]) >= mod)
        ways[l][e] -= mod;
    }
  }
  printf("%I64d\n", ways[m][b]);
  return 0;
}