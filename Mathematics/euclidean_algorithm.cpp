/* ============================= */
/* GCD (greatest common divisor) */
/* ============================= */
// euclid's algorithm
int gcd (int a, int b) {
  int tmp;
  while (b) tmp = a, a = b, b = tmp % b;
  return a;
}

/* ============ */
/* extended GCD */
/* ============ */
// extended euclid's algorithm
// a * x + b * y = d = gcd(a, b)
// x = x0 + n * (b/d)
// y = y0 - n * (a/d)
// where n is integer

// recursive
void xgcd(int a, int b, int& g, int& x, int& y) {
  if (b == 0) { x = 1; y = 0; g = a; return; }
  xgcd(b, a % b, g, x, y);
  int x1 = y, y1 = x - y * (a / b);
  x = x1, y = y1;
}

// iterative
void xgcd(int a, int b, int& g, int& x, int& y)
{
  int x0 = 1, x1 = 0, y0 = 0, y1 = 1;
  int q, r, tmp;
  while (b) {
    q = a / b, r = a % b;
    tmp = x1, x1 = x0 - q * x1, x0 = tmp;
    tmp = y1, y1 = y0 - q * y1, y0 = tmp;
    a = b, b = r;
  }
  g = a, x = x0, y = y0;
}

/* ====================== */
/* multiplicative inverse */
/* ====================== */
int mulinv(int a, int m) {
  int g, x, y; xgcd(a, m, g, x, y);
  if (g == 1) return x % m;
  return -1;
}