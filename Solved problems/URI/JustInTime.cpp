// tags: primality check, sieve of eratosthenes
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)

vector<int> get_primes(int n) {
    vector<bool> is_prime(n, true);
    int limit = (int)floor(sqrt(n));
    rep(i,2,limit)
        if (is_prime[i])
            for (int j = i*i; j <= n; j += i)
                is_prime[j] = false;
    vector<int> primes;
    rep(i,2,n) if (is_prime[i]) primes.push_back(i);
    return primes;
}

int main() {
    int n; scanf("%d", &n);
    vector<int> primes = get_primes((int)floor(sqrt(n)));
    while (true) {
        bool is_prime = true;
        for (int p : primes) if (n % p == 0) {is_prime = false; break;}
        if (is_prime) break;
        n--;
    }
    printf("%d\n", n);
    return 0;
}