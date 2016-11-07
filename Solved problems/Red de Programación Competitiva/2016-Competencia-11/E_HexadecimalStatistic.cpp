// tags: dijkstra, implicit graph, bitwise operations, combinatorics

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
typedef unsigned int uint;

int N;
ll sums[1 << 16];

int char_to_digit(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  return 10 + c - 'a';
}

ll eval(string& num, uint bits) {
  ll val = 0;
  rep(i,0,(int)num.size()-1) {
    int d = char_to_digit(num[i]);
    if ((bits >> d) & 1) {
      val = (val << 4) + d;
    }
  }
  return val;
}


struct Pair {
  int u;
  ll cost;
};

struct greater_cmp {
  bool operator()(const Pair& a, const Pair& b) {
    return a.cost > b.cost;
  }
};

struct less_cmp {
  bool operator()(const Pair& a, const Pair& b) {
    return a.cost < b.cost;
  }
};


ll min_path_sum() {
  static ll mincost[0x10000];

  memset(mincost, -1, sizeof mincost);
  priority_queue<Pair, vector<Pair>, greater_cmp> q;

  int start = 0xffff;
  q.push({start, 0});
  mincost[start] = 0;

  while (!q.empty()) {
    Pair p = q.top(); q.pop();
    if (p.cost > mincost[p.u])
      continue;

    rep (i, 0, 15) {
      if ((p.u >> i) & 1) {
        int v = p.u & ~(1 << i);
        if (mincost[v] == -1 or mincost[v] > p.cost + sums[v]) {
          mincost[v] = p.cost + sums[v];
          q.push({v, mincost[v]});
        }
      }
    }
  }

  return mincost[0];
}

ll max_path_sum() {
  static ll maxcost[0x10000];

  memset(maxcost, -1, sizeof maxcost);
  priority_queue<Pair, vector<Pair>, less_cmp> q;

  int start = 0xffff;
  q.push({start, 0});
  maxcost[start] = 0;

  while (!q.empty()) {
    Pair p = q.top(); q.pop();
    if (p.cost < maxcost[p.u])
      continue;

    rep (i, 0, 15) {
      if ((p.u >> i) & 1) {
        int v = p.u & ~(1 << i);
        if (maxcost[v] == -1 or maxcost[v] < p.cost + sums[v]) {
          maxcost[v] = p.cost + sums[v];
          q.push({v, maxcost[v]});
        }
      }
    }
  }

  return maxcost[0];
}

string to_hex(ll num) {
  static char buff[100];
  static const char* hexdigits = "0123456789abcdef";
  buff[99] = '\0';
  int i = 98;
  do {
    buff[i--] = hexdigits[num & 0xf];
    num >>= 4;
  } while (num);
  return string(buff+i+1);
}

const ll M = 0x3b9aca07;

ll mod_sum(ll a, ll b) {
  return ((a % M) + (b % M)) % M;
}

ll mod_mult(ll a, ll b) {
  return ((a % M) * (b % M)) % M;
}

int main() {

  ll fact[17];
  fact[0] = 1;
  rep(i,1,16) fact[i] = ((ll)i * fact[i-1]) % M;

  while (scanf("%x\n", &N) == 1) {

    vector<string> nums(N);
    rep(i,0,N-1) {
      getline(cin, nums[i]);
    }

    ll totsum = 0;

    for (uint b = 0; b < 0xffff; ++b) {
      ll sum = 0;
      for (string& num : nums)
        sum += eval(num, b);
      sums[b] = sum;

      int n = __builtin_popcount(b);
      totsum = mod_sum(totsum, mod_mult(sum, mod_mult(fact[n], fact[16-n])));
    }

    ll minsum = min_path_sum();
    ll maxsum = max_path_sum();

    string hex_minsum = to_hex(minsum);
    string hex_maxsum = to_hex(maxsum);
    string hex_totsum = to_hex(totsum);

    printf("%s %s %s\n", hex_minsum.c_str(), hex_maxsum.c_str(), hex_totsum.c_str());
  }

  return 0;
}