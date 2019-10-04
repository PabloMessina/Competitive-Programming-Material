typedef long long int ll;

inline ll mod(ll x, ll m) { return ((x %= m) < 0) ? x+m : x; }

/* ============================= */
/* GCD (greatest common divisor) */
/* ============================= */
// OPTION 1: using C++ builtin function __gcd
__gcd(a,b)
// OPTION 2: manually usings euclid's algorithm
int gcd (ll a, ll b) {
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

// --- version 1: iterative
ll gcdext(ll a, ll b, ll& x, ll& y) {
    ll r2, x2, y2, r1, x1, y1, r0, x0, y0, q;
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
    ll g = r2; x = x2, y = y2;
    if (g < 0) g = -g, x = -x, y = -y; // make sure g > 0
    // for debugging (in case you think you might have bugs)
    // assert (g == a * x + b * y);
    // assert (g == __gcd(abs(a),abs(b)));
    return g;
}

// --- version 2: recursive
ll gcdext(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0, y = 1;
        return b;
    }
    ll x1, y1;
    ll g = gcdext(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return g;
}

/* ====================== */
/* multiplicative inverse */
/* ====================== */
// find x such that a * x = 1 (mod m)
// this is the same as finding x, y such that
// a * x + m * y = 1, which can be done with gcdext
// and then returning x (mod m)
ll mulinv(ll a, ll m) {
    ll x, y;
    if (gcdext(a, m, x, y) == 1) return mod(x, m); // make sure 0 <= x < m
    return -1; // no inverse exists
}

/* =========================== */
/* Linear Diophantine Equation */
/* =========================== */
// recommended readings:
// http://gauss.math.luc.edu/greicius/Math201/Fall2012/Lectures/linear-diophantine.article.pdf
// http://mathonline.wikidot.com/solutions-to-linear-diophantine-equations

// find intengers x and y such that a * x + b * y = c
bool lindiopeq(ll a, ll b, ll c, ll& x, ll& y) {
    if (a == 0 and b == 0) { // special case
        if (c == 0) { x = y = 0; return true; }
        return false;
    }
    // general case
    ll s, t;
    ll g = gcdext(a,b,s,t);
    if (c % g == 0) {
        x = s*(c/g), y = t*(c/g);
        return true;
    }
    return false;
}

/* ========================== */
/* Linear Congruence Equation */
/* ========================== */
// recommended reading:
// http://gauss.math.luc.edu/greicius/Math201/Fall2012/Lectures/linear-congruences.article.pdf

// find smallest integer x (mod m) that solves the equation
//   a * x = b (mod m)
bool lincongeq(ll a, ll b, ll m, ll& x) {
    assert (m > 0);
    a = mod(a,m);
    b = mod(b,m);    
    ll s, t;
    ll g = gcdext(a,m,s,t);
    if (b % g == 0) {
        ll bb = b/g;
        ll mm = m/g;
        ll n = -s*bb/mm;
        x = s*bb + n*mm;
        if (x < 0) x += mm;
        // for debugging
        // assert (0 <= x and x < m);
        // assert (mod(a*x,m) == b);
        return true;
    }
    return false;
}