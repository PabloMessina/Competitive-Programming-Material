// tags: integer root square

#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;

const int MAXN = (int)1e6;

ll a00, a11, a10, a01;
ll n0, n1, n;
char buff[MAXN+1];

ll isqrt(ll x) {
  ll y = x;
  while (true) {
    ll y1 = (y + x/y) / 2;
    if (y == y1) break;
    y = y1;
  }
  return y;
}
bool isPerfectSquare(ll x, ll& root) {
  root = isqrt(x);
  return root * root == x;
}

int main() {
  scanf("%I64d%I64d%I64d%I64d", &a00, &a01, &a10, &a11);
  ll d00, d11;

  if (!isPerfectSquare(1+8*a00, d00) ||
      !isPerfectSquare(1+8*a11, d11)) {
    puts("Impossible");
    return 0;
  }

  // + +
  n0 = (1 + d00) / 2;
  n1 = (1 + d11) / 2;
  if (n0 * n1 == a01 + a10) goto possible;

  // + -
  n0 = (1 + d00) / 2;
  n1 = (1 - d11) / 2;
  if (n1 >= 0 && (n0 * n1 == a01 + a10)) goto possible;

  // - +
  n0 = (1 - d00) / 2;
  n1 = (1 + d11) / 2;
  if (n0 >= 0 && (n0 * n1 == a01 + a10)) goto possible;

  puts("Impossible");
  return 0;

  possible:
  n = n0 + n1;

  if (n1 > 0) {
    memset(buff, '1', sizeof(buff[0]) * n);
    ll b = a10 % n1;
    ll k = a10 / n1;
    ll r = n0 - k - (b > 0 ? 1 : 0);
    if (r > 0) memset(buff, '0', sizeof(buff[0]) * r);
    if (b > 0) buff[r + b] = '0';
    if (k > 0) memset(buff + (n0 - k) + n1, '0', sizeof(buff[0]) * k);
  } else {
    memset(buff, '0', sizeof(buff[0]) * n);
  }
  printf("%.*s\n", (int)n, buff);
  return 0;
}