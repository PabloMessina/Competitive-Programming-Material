// tags: greedy
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
int main() {
  int n,k;
  scanf("%d%d",&n,&k);
  priority_queue<int> pq;
  vector<int> prices(n);
  rep(i,0,n-1) scanf("%d", &prices[i]);
  int totcost = 0;
  invrep(i,n-1,0) {
    pq.push(prices[i]);
    totcost += prices[i];
    if ((i+1) % (k+1) == 0)
      totcost -= pq.top(), pq.pop();
  }
  printf("%d\n", totcost);
  return 0;
}