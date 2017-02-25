// tags: geometry, combinatorics, DP
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;

const int MAXN = 1000;
const ll MOD = 1000000007ll;

struct Point {
  double x,y;
  bool operator<(const Point& p) const {
    if (x == p.x) return y < p.y;
    return x < p.x;
  }
};

int main() {
  int n; scanf("%d", &n);

  double xs[n], ys[n];
  set<Point> points;
  map<Point, int> midcounts;

  // read points
  rep(i,0,n-1) {
    double x, y; scanf("%lf%lf",&x,&y);
    xs[i] = x, ys[i] = y;
    points.insert({x,y}); // collect points
  }

  // count segments per middle point
  rep(i,0,n-2) rep(j,i+1,n-1) {
    Point mid = {(xs[i]+xs[j])*0.5, (ys[i] + ys[j])*0.5};
    auto res = midcounts.insert(make_pair(mid, 1));
    if (!res.second) res.first->second++;
  }

  // pre-compute choose matrix
  ll choose[n+1][n+1];
  rep(m,1,n) {
    choose[m][0] = choose[m][m] = 1;
    rep(k,1,m-1) choose[m][k] = (choose[m-1][k] + choose[m-1][k-1]) % MOD;
  }

  // count self-rotating subsets
  vector<ll> counts(n+1, 0);
  counts[1] = n;
  for (auto& kv : midcounts) {
    bool midfound = points.count(kv.first) > 0;
    int segcount = kv.second;
    rep(k, 1, segcount) {
      ll c = choose[segcount][k]; // choose k segments
      counts[2*k] = (counts[2*k] + c) % MOD; // k segments -> 2*k points
      if (midfound) counts[2*k+1] = (counts[2*k+1] + c) % MOD; // k segments + middle -> 2*k+1 points
    }
  }

  // print answer
  printf("%lld", counts[1]);
  rep(k,2,n) printf(" %lld", counts[k]);
  puts("");
  return 0;
}