// tags: DP, top-down
#include <bits/stdc++.h>
using namespace std;

#define MAXN 5000
#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef long long int ll;

int N, M, K;
ll acc[MAXN];

ll inline rsq(int i, int j) {
  return acc[j] - (i>0? acc[i-1] : 0);
}

ll memo[MAXN+1][MAXN];

ll dp(int k, int i) {
  if (k == 0) return 0;
  if (i + k * M > N) return 0;
  if (memo[k][i] != -1) return memo[k][i];
  return memo[k][i] = max(
    rsq(i, i+M-1) + dp(k-1, i+M),
    dp(k, i+1)
  );
}

int main() {
  scanf("%d%d%d", &N, &M, &K);
  ll prev = 0;
  rep(i,0,N-1) {
    scanf("%I64d", &acc[i]);
    acc[i] += prev;
    prev = acc[i];
  }
  memset(memo, -1, sizeof memo);
  printf("%I64d\n", dp(K,0));
  return 0;
}