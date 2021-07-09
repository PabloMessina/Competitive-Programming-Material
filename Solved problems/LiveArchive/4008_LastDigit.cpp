// tags: math, sieve of eratosthenes, binary modular exponentiation,
// prime factorization of factorials
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXN = 1000000;
int freq[26];
int exps[MAXN];
vector<int> primes;

vector<int> sieve(int n) { // sieve of eratosthenes
    vector<bool> isprime(n+1, true);
    int limit = (int)floor(sqrt(n));
    rep(x,2,limit+1) {
        if (isprime[x]) {
            for (int y=x*x; y<=n; y+=x) isprime[y] = false;
        }
    }
    vector<int> primes;
    rep(x,2,n+1) if (isprime[x]) primes.push_back(x);
    return primes;
}

void factorial_prime_factorization(int x, int sign) { // factorización prima de x!
    for (int p : primes) {
        if (p > x) break;
        int e = 0;
        int tmp = x;
        while ((tmp /= p) > 0) e += tmp;
        if (sign > 0) exps[p] = e;
        else exps[p] -= e;
    }
}

int binary_exp(int a, int b, int m) {	
    a %= m;
    int res = 1;
    while (b > 0) {
        if (b&1) res = (res * a) % m;
        a = (a * a) % m;
        b >>= 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    primes = sieve(MAXN);
    string line;	
    while (cin >> line) {
        memset(freq, 0, sizeof freq);		
        for (char c : line) freq[c-'a']++;
        int n = line.size();		
        factorial_prime_factorization(n, 1);		
        rep(i,0,26) factorial_prime_factorization(freq[i], -1);		
        int n_zeroes = min(exps[2], exps[5]);
        exps[2] -= n_zeroes;
        exps[5] -= n_zeroes;
        int res = 1;
        for (int p : primes) {
            if (p > n) break;
            res = (res * binary_exp(p, exps[p], 10)) % 10;
        }
        cout << res << '\n';
    }
    return 0;
}
