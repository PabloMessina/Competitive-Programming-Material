// tags: geometry, combinatorics, modular multiplicative inverse
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

// ----- multiplicative inverse ------------

void xgcd(ll a, ll b, ll&g, ll&x, ll& y) {
  ll x0 = 1, x1 = 0, y0 = 0,  y1 = 1;
  ll q, r, tmp;
  while (b) {
    q = a / b, r = a % b;
    tmp = x1, x1 = x0 - q*x1, x0 = tmp;
    tmp = y1, y1 = y0 - q*y1, y0 = tmp;
    a=b,b=r;
  }
  g=a, x=x0, y=y0;
}

ll multinv(ll a, ll m) {
  ll g,x,y; xgcd(a,m,g,x,y);
  if (g == 1) return (x+m) % m;
  return -1;
}

// ------ choose_mod(n, k) ------------

ll fac[MAXN + 1];
void init_fact(int n) {
  fac[0] = 1;
  rep(i,1,n) fac[i] = (i * fac[i-1]) % MOD;
}

ll mult(ll a, ll b) {
  return (a * b) % MOD;
}

ll choose_memo[MAXN+1][MAXN+1];
ll choose_mod(ll n, ll k) {
  if (choose_memo[n][k] != -1) return choose_memo[n][k];
  return choose_memo[n][k] = mult(fac[n], multinv(mult(fac[k], fac[n-k]), MOD));
}

// ---- main -------

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

  // prepare for counting self-rotating subsets
  memset(choose_memo, -1, sizeof choose_memo);
  init_fact(n);

  // count self-rotating subsets
  vector<ll> counts(n+1, 0);
  counts[1] = n;
  for (auto& kv : midcounts) {
    bool midfound = points.count(kv.first) > 0;
    int segcount = kv.second;
    rep(k, 1, segcount) {
      ll c = choose_mod(segcount, k); // choose k segments
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