// tags: math, implementation
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define rep(i,a,b) for(int i=a; i<=b; ++i)


int main() {
  int e, m, x;
  int _case = 1;
  while(scanf("%d%d",&e,&m) == 2) {
    e = (365 - e) % 365;
    m = (687 - m) % 687;
    for (x = 0; x < 365*687; ++x) {
      int re = x % 365;
      int rm = x % 687;
      if (re == e && rm == m) break;
    }
    printf("Case %d: %d\n", _case, x);
    _case++;
  }
  return 0;
}