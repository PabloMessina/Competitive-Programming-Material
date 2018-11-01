// tags: math, primes, greedy, binomial/multinomial coefficients, DP,
// combinatorics, exhaustive search, pruning, numerical overflow detection
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef unsigned long long int ull;
// -------------------------------

const ull MAX = 1ull << 63;
ull primes[15] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
int exponent[15]; // store exponent for each prime

// multiply x and y and also check if there is overflow
ull mul(ull x, ull y, bool& overflow) {
    ull m = x*y;
    overflow = !(m/x == y and m < MAX);
    return m;
}

// add x and y and also check if there is overflow
ull add(ull x, ull y, bool& overflow) {
    overflow = MAX - x < y;
    return x + y;
}

// choose(n,k,overflow):
// it computes the binomial coefficient C(n,k) = n!/(k!*(n-k)!)
// using the recurrence relation C(n,k) = C(n-1,k) + C(n-1,k-1)
// We use dynamic programming over this recurrence.
// The argument bool& overflow is used to tell the caller whether
// the function incurred in a numerical overflow
ull memo_ull[100][100];
bool memo_bool[100][100];
bool memo_overflow[100][100];
ull choose(int n, int k, bool& overflow) {
    ull& ans = memo_ull[n][k];
    bool& o = memo_overflow[n][k];
    if (memo_bool[n][k]) {
        overflow = o;
        return ans;
    }
    memo_bool[n][k] = true;
    if (k == 0) { o = overflow = false; return ans = 1; }
    if (n == k) { o = overflow = false; return ans = 1; }
    if (n < k) { o = overflow = false; return ans = 0; }
    bool o1, o2;
    ull c1 = choose(n-1,k,o1);
    ull c2 = choose(n-1,k-1,o2);
    ans = add(c1, c2, o);
    if (o1 or o2) o = true;
    overflow = o;
    return ans;
}

// Computes the multinomial (e0 + ... + ei)! / (e0! * ... * ei!)
// where e0, ..., ei are the exponents of the first i prime numbers.
// The multinomial itself is computed as the multiplication of many
// binomials, based on the equation shown here:
// https://math.stackexchange.com/a/204209/503889
// The argument bool& overflow is used to tell the caller whether
// the function incurred in a numerical overflow
ull multinomial(int i, bool& overflow) {
    if (i == 0) {
        overflow = false;
        return 1;
    }
    int n = exponent[0];
    ull ans = 1;
    rep(j,1,i) {
        int e = exponent[j];
        n += e;
        ull c = choose(n, e, overflow);
        if (overflow) return 0;
        ans = mul(ans, c, overflow);
        if (overflow) return 0;
    }
    overflow = false;
    return ans;
}

// we keep track of the minimun k for each n
umap<ull,ull> n2k;
void update(ull n, ull k) {
    auto ret = n2k.emplace(n, k);
    if (!ret.second) {
        ull& x = ret.first->second;
        if (x > k) x = k;
    }
}

// Given a valid number k constructed with
// primes 0 .. i-1, search all valid ways to add
// prime factors from i ... 15, such that the exponent
// for the current i-th prime is <= maxe
// For each valid number found, compute the multinomial
// from the exponents of its prime factors an update the
// global n2k umap
void search(int i, int maxe, ull k) {
    if (i == 15) return;
    bool o;
    rep(e,1,maxe) {
        exponent[i] = e;
        k = mul(k, primes[i], o);
        if (o) return;
        
        ull n = multinomial(i, o);
        if (!o) update(n, k);

        search(i+1, e, k);
    }
}

int main() {
    memset(memo_bool, 0, sizeof memo_bool);
    search(0, 62, 1);
    ull n;
    while (cin >> n) cout << n << " " << n2k[n] << endl;
    return 0;
}