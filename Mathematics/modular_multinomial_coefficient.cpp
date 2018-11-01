typedef long long int ll;
const ll MOD = 1000000007ll; // a prime number
const int MAXN = 1000;

/* ===================== */
/*  MODULAR MULTINOMIAL  */
/* ===================== */

ll memo[MAXN+1][MAXN+1];
ll choose(int n, int k) {
    ll& ans = memo[n][k];
    if (ans != -1) return ans;
    if (k == 0) return ans = 1;
    if (n == k) return ans = 1;
    if (n < k) return ans = 0;
    return ans = (choose(n-1,k) + choose(n-1,k-1)) % MOD;
}

// reference: https://math.stackexchange.com/a/204209/503889
ll multinomial(vector<int> ks) {
    int n = 0;
    ll ans = 1;
    for (int k : ks) {
        n += k;
        ans = (ans * choose(n,k)) % MOD;
    }
    return ans;
}