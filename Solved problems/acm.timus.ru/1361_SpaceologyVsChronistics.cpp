// tags: gcd, gcdext, extended euclid algorithm
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;++i)
typedef long long int ll;
typedef vector<int> vi;
typedef vector<ll> vll;
const ll INF = (ll)1e18;

int n, s1, s2;
vector<vi> g;
vector<bool> inloop1;
vector<bool> inloop2;
vector<ll> time1;
vector<ll> time2;
ll T1, T2;

void gcdext(ll a, ll b, ll& d, ll& x, ll& y) {
  if (b == 0) { x = 1; y = 0; d = a; return; }
  gcdext(b, a % b, d, x, y);
  ll x1 = y;
  ll y1 = x - y * (a / b);
  x = x1;
  y = y1;
}

int main() {
  scanf("%d", &n);
  g.assign(n,vi());
  inloop1.assign(n,false);
  inloop2.assign(n,false);
  time1.assign(n,-1);
  time2.assign(n,-1);
  // build graph
  rep(i,0,n-1) {
    while(true) {
      int j; scanf("%d", &j); --j;
      if (j >= 0) g[i].push_back(j);
      else break;
    }
  }
  // simulate
  scanf("%d%d",&s1,&s2); --s1, --s2;
  int prev, curr;
  ll t;
  // first person
  t = 0;
  curr = s1;
  time1[s1] = 0;
  while (true) {
    prev = curr;
    curr = g[curr].front();
    if (time1[curr] == -1) {
      time1[curr] = ++t;
    } else { // loop found
      T1 = time1[prev] - time1[curr] + 1;
      do {
        inloop1[curr] = true;
        curr = g[curr].front();
      } while (!inloop1[curr]);
      break;
    }
  }
  // second person
  curr = s2;
  t = 0;
  time2[s2] = 0;
  while (true) {
    prev = curr;
    curr = g[curr].back();
    if (time2[curr] == -1) {
      time2[curr] = ++t;
    } else { // loop found
      T2 = time2[prev] - time2[curr] + 1;
      do {
        inloop2[curr] = true;
        curr = g[curr].back();
      } while (!inloop2[curr]);
      break;
    }
  }
  // find first meeting time
  t = INF;
  rep(i, 0, n-1) {
    if (time1[i] != -1 && time2[i] != -1) {

      ll x0, y0;
      ll d, dt;

      if (time1[i] == time2[i]) {

        t = min(t, time1[i]);

      } else if (inloop1[i] && inloop2[i]) {

        gcdext(T1, T2, d, x0, y0);
        dt = time2[i] - time1[i];
        if (dt % d == 0) {
          ll r = dt / d;
          double n1 = - (double)(x0 * dt) / (double) T2;
          double n2 = (double)(y0 * dt) / (double) T1;
          ll n = (ll)ceil(max(n1, n2));

          ll k1 = r * x0 + (T2 / d) * n;
          ll t1 = time1[i] + k1 * T1;

          t = min(t, time1[i] + T1 * k1);
        }

      } else if (inloop1[i]) {

        if (time1[i] < time2[i]) {
          int dt = time2[i] - time1[i];
          if (dt % T1 == 0) t = min(t, time2[i]);
        }

      } else if (inloop2[i]) {

        if (time2[i] < time1[i]) {
          int dt = time1[i] - time2[i];
          if (dt % T2 == 0) t = min(t, time1[i]);
        }

      }
    }
  }
  // answer
  printf("%lld\n", (t == INF) ? -1 : t);
  return 0;
}