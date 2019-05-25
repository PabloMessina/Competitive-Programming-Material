// tags: math, primes, segmented sieve of eratosthenes
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 2147483647;

vector<int> get_primes_up_to(int n) {
    vector<bool> isprime(n+1, true);
    int limit = (int)floor(sqrt(n));
    rep(x,2,limit) {
        if (isprime[x]) {
            for (int y=x*x; y<=n; y+=x) {
                isprime[y] = false;
            }
        }
    }
    vector<int> primes;
    rep(x,2,n) if (isprime[x]) primes.push_back(x);
    return primes;
}

int main() {
    // we find all primes up to sqrt(2147483647)
    vector<int> all_primes = get_primes_up_to((int)floor(sqrt(MAXN)));    
    int t; scanf("%d", &t); // read number of test cases
    vector<bool> isprime;
    isprime.reserve(1000001);
    while (t--) { // for each test case
        int l, u; scanf("%d%d", &l, &u); // read L and U
        isprime.assign(u-l+1, true); // we will find all primes in range [L, U]
        int limit = (int) floor(sqrt(u)); // only consider primes <= sqrt(u)
        for (ll p : all_primes) {
            if (p > limit) break;
            ll miny = max(p, (l/p+(l%p>0)))*p; // minimum multiple of p >= l
            for (ll y = miny; y <= u; y += p) { // similar to sieve of eratosthenes
                isprime[y-l] = false;
            }
        }
        // print all primes in range [L,U]
        rep(x,l,u) if (isprime[x-l]) printf("%d\n", x);
    }
    return 0;
}