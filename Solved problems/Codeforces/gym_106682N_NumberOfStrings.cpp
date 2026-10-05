// tags: combinatorics, math, modular arithmetics, binomial coefficients, fermat's little theorem, modular inverse
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
/*
 * PROBLEM: count strings of length N over an alphabet of size A that contain
 * exactly K palindromic substrings of length 3 (each occurrence counted
 * separately), modulo 998244353.
 *
 * KEY OBSERVATIONS:
 *
 * 1) A length-3 substring s[i..i+2] is a palindrome iff s[i] == s[i+2]
 *    (the middle character is irrelevant). So each of the N-2 windows is
 *    really a constraint on the pair of positions (i, i+2).
 *
 * 2) If we draw an edge i -- i+2 for every window, positions split into two
 *    independent paths ("chains"):
 *        even chain: s[0] - s[2] - s[4] - ...   (ceil(N/2) nodes)
 *        odd chain:  s[1] - s[3] - s[5] - ...   (floor(N/2) nodes)
 *    Every edge of a chain is a window; a window is palindromic iff its edge
 *    connects two equal characters. We tag each edge as "same" or "different".
 *
 * 3) Fix the tags on a chain with m edges, j of them "same". Color the chain
 *    from left to right:
 *        - the first node has A choices,
 *        - a "same" edge forces the next node: 1 choice,
 *        - a "different" edge leaves A-1 choices, NO MATTER which color the
 *          previous node had.
 *    So the number of colorings is A * (A-1)^(m-j), which depends only on how
 *    many edges are "same", not on which ones. There are C(m, j) ways to pick
 *    which edges are "same", hence:
 *        chain(m, j) = C(m, j) * A * (A-1)^(m-j)
 *
 * 4) The two chains are independent, so if the even chain gets k palindromes
 *    and the odd chain gets K-k, the counts multiply. Summing over k:
 *        answer = sum_k chain(m1, k) * chain(m2, K-k)
 *
 * (Bonus: by Vandermonde's identity this collapses to
 *  C(N-2, K) * A^2 * (A-1)^(N-2-K), but the loop is O(N) and fast enough.)
 */

const ll MOD = 998244353; // a prime number (needed for Fermat, see below)

// Fast modular exponentiation (binary exponentiation): computes b^e mod MOD
// in O(log e) multiplications by squaring the base and using the bits of e.
ll power(ll b, ll e) {
    ll r = 1; b %= MOD;
    while (e > 0) {
        if (e & 1) r = r * b % MOD; // current bit of e is 1 -> include b^(2^i)
        b = b * b % MOD;            // b^(2^i) -> b^(2^(i+1))
        e >>= 1;
    }
    return r;
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    ll N, K, A; cin >> N >> K >> A;

    // EDGE CASE N == 1: there are no windows at all, so the number of
    // palindromes is always 0. Every one of the A strings works if K == 0,
    // none otherwise. We handle it separately because the odd chain would be
    // empty (0 nodes), and the formula chain(m, j) assumes at least one node
    // (that's where the leading factor A comes from).
    if (N == 1) {
        cout << (K == 0 ? A : 0) << '\n';
        return 0;
    }

    // Number of EDGES in each chain (= nodes - 1). For N >= 2 both chains have
    // at least one node, so m1, m2 >= 0. Note m1 + m2 = N - 2 = number of
    // windows. Example: N = 5 -> even chain {0,2,4} (m1 = 2),
    // odd chain {1,3} (m2 = 1).
    ll m1 = (N + 1) / 2 - 1; // edges in even chain
    ll m2 = N / 2 - 1;       // edges in odd chain

    // EDGE CASE K > N - 2: we can't have more palindromes than windows.
    // (This also covers N == 2, where there are 0 windows, with any K > 0.)
    // Checking it early also keeps indices like m - j non-negative below.
    if (K > m1 + m2) {
        cout << 0 << '\n';
        return 0;
    }

    // PRECOMPUTATION (all arrays of size N+1, since every n, k, exponent we
    // use is <= N):
    //   fact[i]     = i! mod MOD
    //   inv_fact[i] = (i!)^(-1) mod MOD
    //   pw[i]       = (A-1)^i mod MOD
    vector<ll> fact(N + 1), inv_fact(N + 1), pw(N + 1);
    fact[0] = 1;
    rep(i, 1, N + 1) fact[i] = fact[i - 1] * i % MOD;

    // MODULAR INVERSE VIA FERMAT'S LITTLE THEOREM:
    // If p is prime and a is not a multiple of p, then a^(p-1) = 1 (mod p).
    // Dividing both sides by a gives a^(p-2) = a^(-1) (mod p).
    // So the inverse of a is just power(a, p-2), computed in O(log p).
    // Here a = N! and N <= 10^6 < MOD, so N! has no factor equal to MOD,
    // hence it is not a multiple of MOD and the theorem applies.
    // (Alternative: the extended Euclidean algorithm also works, since
    // gcd(a, p) = 1. Fermat is just shorter to write when p is prime.)
    inv_fact[N] = power(fact[N], MOD - 2);

    // We only need ONE expensive inverse. The rest come for free going
    // backwards, because (i-1)! = i! / i, so:
    //   1 / (i-1)! = i * (1 / i!)   =>   inv_fact[i-1] = inv_fact[i] * i
    invrep(i, N, 1) inv_fact[i - 1] = inv_fact[i] * i % MOD;

    pw[0] = 1;
    rep(i, 1, N + 1) pw[i] = pw[i - 1] * (A - 1) % MOD;

    // Binomial coefficient C(n, k) = n! / (k! (n-k)!), where "dividing" means
    // multiplying by the modular inverses. Returns 0 when k is out of range.
    auto choose = [&](ll n, ll k) -> ll {
        if (k < 0 || k > n) return 0;
        return fact[n] * inv_fact[k] % MOD * inv_fact[n - k] % MOD;
    };

    // Colorings of a chain with m edges, j of them tagged "same", summed over
    // all C(m, j) ways of choosing which edges are "same" (observation 3):
    //   C(m, j) * A * (A-1)^(m-j)
    auto chain = [&](ll m, ll j) -> ll {
        return choose(m, j) * A % MOD * pw[m - j] % MOD;
    };

    // Split the K palindromes between the chains: k on the even chain,
    // K-k on the odd chain. A chain can't have more palindromes than edges,
    // so we need 0 <= k <= m1 and 0 <= K-k <= m2, which gives
    //   max(0, K - m2) <= k <= min(K, m1).
    // Restricting the range this way also guarantees m - j >= 0 inside chain().
    ll ans = 0;
    for (ll k = max(0LL, K - m2); k <= min(K, m1); ++k) {
        // each factor is < MOD < 2^30, so the product fits in a long long
        ans = (ans + chain(m1, k) * chain(m2, K - k)) % MOD;
    }
    cout << ans << '\n';
    return 0;
}
