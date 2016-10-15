#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;

int N, R, K;
ll B[200];
ll jumps[200][200];
ll acc_jumps[200][200];
ll times[200];
bool sick[200];

struct Pair {
  int id; ll time;
  bool operator<(const Pair& p) const {
    return time > p.time;
  }
};

ll get_pos(int i, ll t) {
  // printf("--> get_pos(i=%d, t=%lld)\n", i, t);
  ll nc = t / K;
  int r = t % K;
  ll pos = B[i] + acc_jumps[i][K-1] * nc;
  if (r > 0) pos += acc_jumps[i][r-1];
  // printf("\tpos = %lld, pos %% N = %lld\n", pos, pos % N);
  return pos % N;
}

ll gcd (ll a, ll b) {
  while (b) {
    ll aux = a;
    a = b;
    b = aux % b;
  }
  return a;
}

void gcdext(ll a, ll b, ll& d, ll& x, ll& y) {
  if (b == 0) { x = 1; y = 0; d = a; return; }
  gcdext(b, a % b, d, x, y);
  ll x1 = y;
  ll y1 = x - y * (a / b);
  x = x1;
  y = y1;
}

ll collision_time(int i, int j, ll start_t) {
  // printf("==> collision_time(i=%d, j=%d, start_t=%lld)\n",i,j,start_t);
  int k0 = start_t % K;
  ll col_t = LLONG_MAX;

  if (acc_jumps[i][K-1] < acc_jumps[j][K-1])
    swap(i, j);

  ll a = acc_jumps[i][K-1] - acc_jumps[j][K-1]; 

  if (a == 0) {
    rep (k, 0, K-1) {
      ll tk = start_t + (k - k0 + K) % K;  
      ll b = get_pos(j, tk) - get_pos(i, tk);
      if (b == 0) {
        col_t = min(col_t, tk);
        break;
      }
    }
  } else {
    ll d, x, y;
    gcdext(a, N, d, x, y);    
    rep (k, 0, K-1) {
      ll tk = start_t + (k - k0 + K) % K;
      ll b = get_pos(j, tk) - get_pos(i, tk);
      if (b % d == 0) {
        ll n = (ll)ceil(- x * b / (double)N);
        ll m = x * (b/d) + n * (N/d);
        col_t = min(col_t, tk + m * K);
      }
    }
  }

  return col_t;
}

int main() {
  scanf("%d%d%d", &N, &R, &K);
  rep(i,0,R-1) {
    scanf("%lld", &B[i]); B[i]--;
  }
  rep(i,0,R-1) {
    ll acc = 0;
    rep(k,0,K-1) {
      scanf("%lld", &jumps[i][k]);
      acc += jumps[i][k];
      acc_jumps[i][k] = acc;
    }
  }

  memset(sick, 0, sizeof(bool) * R);
  rep(i, 1, R-1) times[i] = LLONG_MAX;
  times[0] = 0;
  priority_queue<Pair> pq;
  pq.push({0, 0});

  while (!pq.empty()) {
    Pair p = pq.top(); pq.pop();
    if (sick[p.id])
      continue;
    sick[p.id] = true;
    rep(i, 0, R-1) {
      if (i == p.id || sick[i]) continue;
      ll next_t = collision_time(p.id, i, p.time);
      if (next_t < times[i]) {
        pq.push({i, next_t});
        times[i] = next_t;
      }
    }
  }

  ll max_t = -1;
  int count = 0;
  rep(i,0,R-1) if (sick[i]) {    
    count++;
    if (max_t < times[i])
      max_t = times[i];
  }
  printf("%d %lld\n", count, max_t);

  return 0;  
}