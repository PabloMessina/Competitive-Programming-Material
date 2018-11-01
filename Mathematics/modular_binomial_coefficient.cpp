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
void xgcd(ll a, ll b, ll&g, ll&x, ll& y) {
    ll x0 = 1, x1 = 0, y0 = 0,  y1 = 1;
    ll q, r, tmp;
    while (b) {
        q = a / b, r = a % b;
        tmp = x1, x1 = x0 - q*x1, x0 = tmp;
        tmp = y1, y1 = y0 - q*y1, y0 = tmp;
        a=b,b=r;
    }
    g=a, x=x0, y=y0;
}
ll multinv(ll a, ll mod) {
    ll g,x,y; xgcd(a,mod,g,x,y);
    if (g == 1) return (x+mod) % mod;
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
ll mult(ll a, ll b) { return (a * b) % MOD; }
ll choose_mod(int n, int k) {
    if (choose_memo[n][k] != -1) return choose_memo[n][k];
    return choose_memo[n][k] = mult(fac[n], multinv(mult(fac[k], fac[n-k]), MOD));
}


