// tags: DP, counting with maps
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;

const int MAXN = (int)1e5;
int n;
int totnums;
map<ll,ll> numToCount;

ll dp() {
  ll prev_val1 = 0;
  ll prev_val2 = 0;
  ll curr_val;

  ll prev_num = -999;
  ll curr_num;
  ll count;

  for (auto it = numToCount.begin(); it != numToCount.end(); ++it) {
    curr_num = it->first;
    count = it->second;

    if (prev_num + 1 == curr_num) {
      curr_val = max(
        prev_val1,
        curr_num * count + prev_val2
      );
    } else {
      curr_val = curr_num * count + prev_val1;
    }

    prev_val2 = prev_val1;
    prev_val1 = curr_val;
    prev_num = curr_num;
  }

  return curr_val;
}

int main() {
  scanf("%I64d",&n);

  rep(i, 1, n) {
    ll x; scanf("%lld", &x);
    auto res = numToCount.insert({x, 1});
    if (!res.second) res.first->second++;
  }

  printf("%I64d\n", dp());

  return 0;
}