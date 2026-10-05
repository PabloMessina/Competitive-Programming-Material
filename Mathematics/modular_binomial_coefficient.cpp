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
rep(m,1,MAXN+1) {
    choose[m][0] = choose[m][m] = 1;
    rep(k,1,m) choose[m][k] = (choose[m-1][k] + choose[m-1][k-1]) % MOD;
}

// -------------------------------------------------
// method 2: factorials + inverse factorials (RECOMMENDED for large n, MOD prime)
// precompute in O(MAXN), then each query is O(1), with no MAXN x MAXN table,
// so it works for MAXN ~ 1e6 or more.
//   fac[i]     = i! (mod MOD)
//   inv_fac[i] = (i!)^-1 (mod MOD)
//   choose(n,k) = fac[n] * inv_fac[k] * inv_fac[n-k] (mod MOD)
// only ONE modular inverse is needed (of MAXN!), via Fermat's little theorem
// (mulinv_fermat in euclidean_algorithm.cpp). Requires MAXN < MOD, so that
// MAXN! is not a multiple of MOD.
// The rest are filled backwards, since (i-1)! = i! / i:
//   1 / (i-1)! = i * (1 / i!)  =>  inv_fac[i-1] = inv_fac[i] * i
ll fac[MAXN+1], inv_fac[MAXN+1];
void init() {
    fac[0] = 1;
    rep(i,1,MAXN+1) fac[i] = fac[i-1] * i % MOD;
    inv_fac[MAXN] = binary_exp(fac[MAXN], MOD-2, MOD); // Fermat
    invrep(i,MAXN,1) inv_fac[i-1] = inv_fac[i] * i % MOD;
}
ll choose(int n, int k) {
    if (k < 0 or k > n) return 0;
    return fac[n] * inv_fac[k] % MOD * inv_fac[n-k] % MOD;
}

// -------------------------------------------------
// method 3: factorials and multiplicative inverse
// n! / (k! * (n-k)!) =  n! * (k! * (n-k)!)^-1  (MOD N)
// we need to find the multiplicative inverse of (k! * (n-k)!) MOD N

ll fac[MAXN+1];
ll choose_memo[MAXN+1][MAXN+1];
void init() {
    fac[0] = 1;
    rep(i,1,MAXN+1) fac[i] = (i * fac[i-1]) % MOD;
    memset(choose_memo, -1, sizeof choose_memo);
}
ll choose_mod(int n, int k) {
    if (choose_memo[n][k] != -1) return choose_memo[n][k];
    return choose_memo[n][k] = mul(fac[n], mulinv(mul(fac[k], fac[n-k])));
}


