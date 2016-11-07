#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;

int main() {
  int n;
  ll eight = 8;
  ll ans = 1;
  scanf("%d", &n);
  while(n--) {
    ans *= eight;
  }
  printf("%lld\n", ans);
  return 0;
}