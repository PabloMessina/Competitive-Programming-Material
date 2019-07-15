#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
const ll MOD = 1000000007ll; // a prime number
const int MAXN = 1000;

/* ================== */
/*  MODULAR BINOMIAL  */
/* ================== */
// choose_mod(n,k) = n! / (k! * (n-k)!) % MOD

// ---------------------
// method 1: DP
// choose(n,k) = (choose(n-1,k-1) + choose(n-1,k)) % MOD
// choose(n,0) = choose(n,n) = 1

// 1.1) DP top-down
ll memo[MAXN+1][MAXN+1];
ll choose(int n, int k) {
    ll& ans = memo[n][k];
    if (ans != -1) return ans;
    if (k == 0) return ans = 1;
    if (n == k) return ans = 1;
    if (n < k) return ans = 0;
    return ans = (choose(n-1,k) + choose(n-1,k-1)) % MOD;
}

// 1.2) DP bottom-up
ll choose[MAXN+1][MAXN+1];
rep(m,1,MAXN) {
    choose[m][0] = choose[m][m] = 1;
    rep(k,1,m-1) choose[m][k] = (choose[m-1][k] + choose[m-1][k-1]) % MOD;
}

// -------------------------------------------------
// method 3: factorials and multiplicative inverse
// n! / (k! * (n-k)!) =  n! * (k! * (n-k)!)^-1  (MOD N)
// we need to find the multiplicative inverse of (k! * (n-k)!) MOD N


// --- multiplicative inverse --
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
    if (g < 0) g = -g, x = -x, y = -y;
    return g;
}
ll inline mod(ll x) { return ((x %= MOD) < 0) ? x+MOD : x; }
ll inline mul(ll a, ll b) { return (a*b) % MOD; }
ll mulinv(ll a) {
    ll x, y;
    if (gcdext(a, m, x, y) == 1) return mod(x);
    return -1;
}

// -- choose_mod(n, k) --
ll fac[MAXN+1];
ll choose_memo[MAXN+1][MAXN+1];
void init() {
    fac[0] = 1;
    rep(i,1,MAXN) fac[i] = (i * fac[i-1]) % MOD;
    memset(choose_memo, -1, sizeof choose_memo);
}

ll choose_mod(int n, int k) {
    if (choose_memo[n][k] != -1) return choose_memo[n][k];
    return choose_memo[n][k] = mul(fac[n], mulinv(mul(fac[k], fac[n-k])));
}


