// tags: prime numbers, sieve of eratosthenes
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

uset<ll> get_primes_squared(int n) {
    vector<bool> is_prime(n + 1, true);
    int limit = (int) floor(sqrt(n));
    rep(i,2,limit) {
        if (is_prime[i]) {
            for (int j=i*i; j <= n; j+=i) {
                is_prime[j] = false;
            }
        }
    }
    uset<ll> primes_squared;
    rep(i,2,n) if (is_prime[i]) primes_squared.insert((ll)i * (ll)i);
    return primes_squared;
}

int main() {
    uset<ll> primes_squared = get_primes_squared(1000000);
    int n;
    scanf("%d", &n);
    while(n--) {
        ll x; scanf("%I64d", &x);
        if (primes_squared.find(x) == primes_squared.end()) {
            puts("NO");
        } else {
            puts("YES");
        }
    }
    return 0;
}