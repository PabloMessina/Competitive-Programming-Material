// using sqrt()
bool perfect_square(ll x, ll& root) {
  if (x < 0) return false;
  root = (ll)sqrt(x);
  return (root * root == x || ++root * root == x);
}

// Newton's method
ll isqrt(ll x) {
  ll y0 = x;
  while (true) {
    ll y1 = (y0 +  x / y0) / 2;
    if (y1 == y0) break;
    y0 = y1;
  }
  return y0;
}
bool isPerfectSquare(ll x, ll& root) {
  root = isqrt(x);
  return root * root == x;
}