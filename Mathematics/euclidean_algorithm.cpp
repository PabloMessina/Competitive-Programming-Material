/* ============================= */
/* GCD (greatest common divisor) */
/* ============================= */
// euclid's algorithm
int gcd (int a, int b) {
    while (b) { a %= b; swap(a,b); }
    return a;
}
// or you can also use __gcd(a,b)

/* ============ */
/* extended GCD */
/* ============ */
// extended euclid's algorithm
// a * x + b * y = g = gcd(a, b)
// x = x0 + n * (b/g)
// y = y0 - n * (a/g)
// where n is integer
void xgcd(int a, int b, int&g, int& x, int& y) {
    int r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
    r2 = a, x2 = 1, y2 = 0;
    r1 = b, x1 = 0, y1 = 1;
    while (r1) {
        q = r2 / r1;
        r0 = r2 % r1;
        x0 = x2 - q * x1;
        y0 = y2 - q * y1;
        r2 = r1, x2 = x1, y2 = y1;
        r1 = r0, x1 = x0, y1 = y0;        
    }
    g = r2, x = x2, y = y2;
}

/* ====================== */
/* multiplicative inverse */
/* ====================== */
int mulinv(int a, int m) {
    int g, x, y; xgcd(a, m, g, x, y);
    if (g == 1) {
        int i = x % m;
        return i < 0 ? i+m : i;
    }
    return -1;
}