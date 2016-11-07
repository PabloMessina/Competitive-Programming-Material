#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;


int c, m;
ll memo[101][101];
int p[100][101];

ll dp(int x, int i) {
  if (x == 0 || i == m)
    return 0;
  if (memo[x][i] != -1)
    return memo[x][i];

  ll ans = 0;
  rep(k,0,x) {
    ans = max(ans, p[i][k] + dp(x-k,i+1));
  }
  return memo[x][i] = ans;
}

int main() {
  scanf("%d%d",&c,&m);
  rep(i,0,m-1) {
    p[i][0] = 0;
    rep(j,1,c) {
      scanf("%d", &p[i][j]);
    }
  }
  memset(memo, -1, sizeof memo);
  printf("%lld\n", dp(c,0));

  return 0;
}