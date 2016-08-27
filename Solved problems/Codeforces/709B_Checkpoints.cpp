// tags: greedy
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int n, a;

int main() {
  scanf("%d%d",&n,&a);
  vector<int> dist(n);
  rep(i,0,n-1) {
    scanf("%d", &dist[i]);
  }
  if (n == 1) {
    puts("0");
    return 0;
  }
  sort(dist.begin(), dist.end());
  int d = min(
    dist[n-2] - dist[0] + min(abs(a - dist[0]), abs(dist[n-2] - a)),
    dist[n-1] - dist[1] + min(abs(a - dist[1]), abs(dist[n-1] - a))
  );
  printf("%d\n", d);
  return 0;
}