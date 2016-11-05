// tags: implicit graph, BFS, sieve of eratosthenes

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 1000000

typedef pair<int,int> pii;

vector<bool> is_prime;

void find_primes_up_to(int n) {
  is_prime.assign(n+1, true);
  is_prime[1] = false;
  int limit = (int) floor(sqrt(n));
  rep(i, 2, limit)
    if (is_prime[i])
      for (int j = i*i; j <= n; j += i)
        is_prime[j] = false;
}

int dirs[4][2] = {
  {0, 1},
  {-1, 0},
  {0, -1},
  {1, 0}
};

pii num_to_cell(int x) {

  int n = (int)ceil ((-1 + sqrt(x)) / 2);

  if (n == 0) return pii(0, 0);

  int h = n, v = -n;
  int dirsize = 2 * n;
  int ref = 4*n*(n-1) + 1;
  int steps = x - ref;

  rep(i, 0, 3) {
    if (steps <= dirsize) {
      h += dirs[i][0] * steps;
      v += dirs[i][1] * steps;
      break;
    }
    h += dirs[i][0] * dirsize;
    v += dirs[i][1] * dirsize;
    steps -= dirsize;
  }

  return pii(h,v);
}

int cell_to_num(int h, int v) {
  int n = max(abs(h), abs(v));
  if (n == 0) return 1;
  int offset = 1 + 4*n*(n-1);
  int dirsize = 2*n;

  if (h == n && v > -n) // right
    return offset + v + n;

  if (v == n && h < n) // top
    return offset + dirsize + n - h;

  if (h == -n && v < n) // left
    return offset + dirsize * 2 + n - v;

  // bottom
  return offset + dirsize * 3 + h + n;
}


struct triple {int h, v, num; };

int steps1[MAXN];
int steps2[MAXN];

int path_length(int x, int y) {

  if (x == y) return 0;

  memset(steps1, -1, sizeof steps1);
  memset(steps2, -1, sizeof steps2);
  queue<triple> q1, q2;

  pii c1 = num_to_cell(x);
  pii c2 = num_to_cell(y);

  q1.push({c1.first, c1.second, x});
  q2.push({c2.first, c2.second, y});
  steps1[x] = 0;
  steps2[y] = 0;

  while (!q1.empty() && !q2.empty()) {
    triple t1 = q1.front(); q1.pop();
    triple t2 = q2.front(); q2.pop();

    rep(i,0,3) {
      int h = t1.h + dirs[i][0];
      int v = t1.v + dirs[i][1];
      int num = cell_to_num(h,v);

      if (is_prime[num]) continue;
      if (steps1[num] != -1) continue;

      if (steps2[num] != -1) {
        return steps1[t1.num] + steps2[num] + 1;
      }

      steps1[num] = steps1[t1.num] + 1;
      q1.push({h, v, num});
    }

    rep(i,0,3) {
      int h = t2.h + dirs[i][0];
      int v = t2.v + dirs[i][1];
      int num = cell_to_num(h,v);

      if (is_prime[num]) continue;
      if (steps2[num] != -1) continue;

      if (steps1[num] != -1) {
        return steps1[num] + steps2[t2.num] + 1;
      }

      steps2[num] = steps2[t2.num] + 1;
      q2.push({h, v, num});
    }
  }

  return -1;

}



int main() {

  find_primes_up_to(MAXN);

  int x,y;
  int _case = 1;
  while(scanf("%d%d",&x,&y) == 2) {

    int len = path_length(x,y);
    if (len == -1) {
      printf("Case %d: impossible\n", _case);
    } else {
      printf("Case %d: %d\n", _case, len);
    }

    _case++;
  }
  return 0;
}