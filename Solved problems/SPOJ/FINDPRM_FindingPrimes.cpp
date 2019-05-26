// tags: math, primes, sieve of eratosthenes, DP
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAXN = 10000000;
vector<bool> isprime(MAXN+1, true);
int prime_count[MAXN+1] = {0};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int limit = (int) floor(sqrt(MAXN));
    rep(x,2,limit) {
        if (isprime[x]) {
            for (int y = x*x; y <= MAXN; y+=x) {
                isprime[y] = false;
            }
        }
    }
    rep(x,2,MAXN) prime_count[x] = prime_count[x-1] + isprime[x];
    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        cout << prime_count[n] - prime_count[n>>1] << '\n';
    }
    return 0;
}