#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXS 500

int n, s;
int value[MAXS + 1];
int memo[MAXS+1][MAXS+1];

int dp(int i, int k) {
  if (i > s) return 0;
  if (memo[i][k] != -1)
    return memo[i][k];
  int ans;
  if (i == 1 || i/2 > k) {
    ans = max(value[i] + dp(i+1, k+1), dp(i+1, k));
  } else {
    ans = dp(i+1, k);
  }
  return memo[i][k] = ans;
}

int main() {  
  scanf("%d", &n);
  rep(spree, 1, n) {
    scanf("%d", &s);
    rep(i,1,s) {
      scanf("%d", &value[i]);
    }
    memset(memo, -1, sizeof memo);
    printf("Spree #%d: %d\n", spree, dp(1, 0));
  }
  return 0;
}