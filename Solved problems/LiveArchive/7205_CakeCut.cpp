// tags: polygon area, binary search

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 100000

typedef long long int ll;

struct Point { ll x, y; };

int N;
Point P[MAXN];
ll acc_area[MAXN];
ll tot_area;

ll get_area(int i, int j) {
  ll area;
  if (i < j) {
    area = acc_area[j-1];
    if (i > 0) area -= acc_area[i-1];
  } else {
    area = acc_area[N-1];
    if (j > 0) area += acc_area[j-1];
    if (i > 0) area -= acc_area[i-1];
  }
  area += (P[j].x + P[i].x) * (P[i].y - P[j].y);
  return abs(area);
}

int main() {
  while(scanf("%d", &N) == 1) {

    rep(i, 0, N-1) {
      ll x,y; scanf("%lld%lld", &x, &y);
      P[i] = {x,y};
    }

    tot_area = 0;
    rep(i,0,N-1) {
      int j = (i+1) % N;
      acc_area[i] = tot_area + (P[i].x + P[j].x) * (P[j].y - P[i].y);
      tot_area = acc_area[i];
    }
    tot_area = abs(tot_area);

    ll carol_area = -1;

    rep(i, 0, N-1) {

      int a = (i + 2) % N;
      int b = (i + N-2) % N;
      if (a > b) b += N;

      while (a < b) {
        int m = (a+b)/2;
        int j = m % N;
        ll curr_area = get_area(i, j);
        ll next_area = get_area(i, (j+1)%N);
        ll curr_max = max(tot_area - curr_area, curr_area);
        ll next_max = max(tot_area - next_area, next_area);
        if (next_max >= curr_max) {
          b = m;
        } else {
          a = m+1;
        }
      }

      a %= N;
      ll area = get_area(i, a);
      carol_area = max(carol_area,  max(tot_area - area, area));
    }

    printf("%lld %lld\n", carol_area, (tot_area -  carol_area));
  }


  return 0;
}