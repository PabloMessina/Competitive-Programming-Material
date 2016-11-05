// tag: greedy
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef vector<int> vi;
typedef long long int ll;
int n;
vi costs;
vi times;
int main() {
  scanf("%d",&n);
  costs.resize(n);
  times.resize(n);
  rep(i,0,n-2) scanf("%d", &costs[i]);
  rep(i,0,n-1) scanf("%d", &times[i]);

  int curr_t = 0;
  int curr_i = 0;
  int reach_i = 1;
  ll tot = 0;

  while(true) {
    int next_t = curr_t + (reach_i - curr_i);
    if (times[reach_i] <= next_t) {
      if (reach_i == n-1) {
        rep(i, curr_i, reach_i-1) {
          tot += costs[i];
        }
        break;
      } else  {
        reach_i++;
        if (costs[reach_i-1] < costs[curr_i]) {
          rep(i, curr_i, reach_i-2)
            tot += costs[i];
          curr_t += reach_i-1 - curr_i;
          curr_i = reach_i-1;
        }
      }
    } else {
      int steps = ((times[reach_i] - next_t + 1) / 2) * 2;
      curr_t += steps;
      tot += (ll)costs[curr_i] * (ll)steps;
    }
  }
  printf("%lld", tot);
  return 0;
}