#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)

int main() {
  int n,c,s;
  scanf("%d%d%d", &n,&c,&s);
  vector<int> counts(n, 0);
  counts[0] = 1;
  int i = 0, d;
  while(c--) {
    scanf("%d", &d);
    i = (i + d + n) % n;
    counts[i]++;
  }
  printf("%d\n", counts[s-1]);
  return 0;
}