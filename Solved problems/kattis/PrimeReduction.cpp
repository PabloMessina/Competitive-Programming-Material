// tags: math, primes, sieve of eratosthenes, prime factorization,
// DP, memoization
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define umap unordered_map
// -------------------------------

const int MAXN = 1000000000;
vector<int> primes;

vector<int> get_primes_up_to(int n) {
    vector<bool> isprime(n+1, true);
    int limit = (int) floor(sqrt(n));
    rep(x,2,limit) {
        for(int y=x*x; y<=n; y+=x) isprime[y] = false;
    }
    vector<int> primes;
    rep(x,2,n) if (isprime[x]) primes.push_back(x);
    return primes;
}

umap<int,pair<int,int>> memo;
pair<int,int> prime_reduction(int x) {
    auto it = memo.find(x);
    if (it != memo.end()) return it->second;
    int limit = (int) floor(sqrt(x));
    int sum = 0;
    int orig_x = x;
    for (int p : primes) {
        if (p > limit) break;
        while (x % p == 0) { sum += p; x /= p; }
        if (x == 1) break;
    }
    if (x == orig_x) return memo[x] = { x, 1 };
    if (x > 1) sum += x;
    auto p = prime_reduction(sum);
    return memo[orig_x] = { p.first, p.second + 1};
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    primes = get_primes_up_to((int)floor(sqrt(MAXN)));
    while (true) {
        int x; cin >> x;
        if (x == 4) break;
        auto p = prime_reduction(x);
        cout << p.first << ' ' << p.second << '\n';
    }
    return 0;
}