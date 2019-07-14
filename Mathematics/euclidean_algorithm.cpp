/* ============================= */
/* GCD (greatest common divisor) */
/* ============================= */
// OPTION 1: using C++ builtin function __gcd
__gcd(a,b)
// OPTION 2: manually usings euclid's algorithm
int gcd (int a, int b) {
    while (b) { a %= b; swap(a,b); }
    return a;
}

/* ============ */
/* extended GCD */
/* ============ */
// extended euclid's algorithm: find g, x, y such that
// a * x + b * y = g = gcd(a, b)
// The algorithm finds a solution (x0,y0) but there are infinite more:
//   x = x0 + n * (b/g)
//   y = y0 - n * (a/g)
// where n is integer, are the set of all solutions
int gcdext(int a, int b, int& x, int& y) {
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
    int g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y; // make sure g > 0
    // for debugging (in case you think you might have bugs)
    // assert (g == a * x + b * y);
    // assert (g == __gcd(abs(a),abs(b)));
    return g;
}

/* ====================== */
/* multiplicative inverse */
/* ====================== */
// find x such that a * x = 1 (mod m)
// this is the same as finding x, y such that
// a * x + m * y = 1, which can be done with gcdext
// and then returning x (mod m)
int inline mod(int x, int m) { return ((x %= m) < 0) ? x+m : x; }
int mulinv(int a, int m) {
    int x, y;
    if (gcdext(a, m, x, y) == 1) return mod(x, m); // make sure 0 <= x < m
    return -1; // no inverse exists
}