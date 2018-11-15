// tags: DP, combinatorics, math, bitmasks, bitwise xor,
// modular arithmetics, prime factorization
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------

const int MAXN = 100000;
const ll MOD = 1000000007;
int primes[19] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67};
int freq[71] = {0};
int masks[71];
ll pow2[MAXN+1];

ll inline add(ll x, ll y) { return (x+y) % MOD; }
ll inline mul(ll x, ll y) { return (x*y) % MOD; }

int get_mask(int x) {
    int mask = 0;
    int b = 1;
    rep(i,0,18) {
        while (x > 1 && x % primes[i] == 0) {
            x /= primes[i];
            mask ^= b;
        }
        if (x == 1) break;
        b <<= 1;
    }
    return mask;
}

// dp(i, mask):
//   number of ways to choose array elements with value <= i (1 .. i)
//   such that their product has a prime factorization
//   where the exponents of the prime factors are even/odd according to
//   the bits of mask. i.e:
//   
//   product = p0^e0 * p1^e1 * ... * p18^e18
//   where ei % 2 == (mask >> i) & 1
//     (if the i-th bit in 'mask' is 1, ei should be odd)
//     (if the i-th bit in 'mask' is 0, ei should be even)
//
// Therefore, the solution to the original problem is dp(70, 0) - 1
//   because i=70 means we are considering all elements (all elements are <= 70)
//   and mask = 0 means we want all the exponents to be even
//   (because the product is a perfect square iff all the exponents in the prime
//    factorization are even)
// However, we substract one (- 1) because we need to remove the EMPTY subset
// from the possible ways (the statement says NON-EMPTY subsets)
int memo[71][1 << 19];
int dp(int i, int mask) {
    // base case 1: (i == 0) an empty list
    if (i == 0) return mask == 0;
    // base case 2: problem already solved
    int& ans = memo[i][mask];
    if (ans != -1) return ans;
    // base case 3: value 'i' has frequency 0 (not present in array)
    if (freq[i] == 0) return ans = dp(i-1, mask);
    // general case:
    //  there are 2^(freq[i]-1) ways of choosing even-size subsets of elements with value 'i'
    //  there are 2^(freq[i]-1) ways of choosing odd-size subsets of elements with value 'i'
    //     * proof: https://math.stackexchange.com/questions/459088/sum-k-0n-2-n-choose2k-sum-k-1n-2-n-choose2k-1-combinatori
    //  in the even case, i ^ even_exponent doesn't change the parity of the exponents
    //     in the final product
    //  in the odd case,  i ^ odd_exponent has the same prime factors and the same
    //     prime exponent parities as i (encoded in masks[i])
    //     so, in order to meet 'mask' requirements, i ^ odd_exponent must be multiplied
    //     by a number X such that the resulting prime exponent parity matches 'mask'.
    //     Therefore, X must satisfy the prime exponent parities given by mask XOR masks[i]
    return ans = mul(pow2[freq[i]-1], add(dp(i-1, mask), dp(i-1, mask^masks[i])));
}

int main() {
    pow2[0] = 1;
    rep(i,1,MAXN) pow2[i] = mul(pow2[i-1], 2);
    int n; cin >> n;
    rep(i,0,n-1) { int x; cin >> x; freq[x]++; }    
    rep(i,1,70) masks[i] = get_mask(i);
    memset(memo, -1, sizeof memo);
    cout << add(dp(70,0), MOD-1) << endl;
    return 0;
}