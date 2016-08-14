#include <cstdio>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;

int n;
ll m;
ll memo[10][2001];

ll dp(int i, ll l) {
  if (l << (n-i-1) > m) return 0;
  if (i == n-1) return m - l + 1;
  if (memo[i][l] != -1) return memo[i][l];
  return memo[i][l] = dp(i+1, l*2) + dp(i,l+1);
}

int main() {
  int tt;
  scanf("%d", &tt);
  rep(t,1,tt) {
    scanf("%d%lld",&n,&m);
    memset(memo, -1, sizeof memo);
    printf("Data set %d: %d %lld %lld\n",t,n,m,dp(0, 1));
  }
  return 0;
}