/* ============================= */
/* Binary Modular Exponentiation */
/* ============================= */
int mod_pow(int b, int e, int m) {
	if (e == 1)
		return b % m;
	int he = e / 2;
	int x = mod_pow(b, he, m);
	x = (x * x) % m;
	if (e % 2 == 1)
		x = (x * b) % m;
	return x;
}

/* ============================= */
/* GCD (greatest common divisor) */
/* ============================= */
// euclid algorithm
int gcd (int a, int b) {
  while (b) {
    int aux = a;
    a = b;
    b = aux % b;
  }
  return a;
}

/* ============ */
/* GCD extended */
/* ============ */
// extended euclid algorithm
void gcdext(int a, int b, int& d, int& x, int& y) {
  if (b == 0) { x = 1; y = 0; d = a; return; }
  gcdext(b, a % b, d, x, y);
  int x1 = y;
  int y1 = x - y * (a / b);
  x = x1;
  y = y1;
}