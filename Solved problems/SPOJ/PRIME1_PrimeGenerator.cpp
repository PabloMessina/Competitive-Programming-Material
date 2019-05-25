// #pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

vector<int> get_primes_up_to(int n) {
    vector<bool> is_prime(n+1, true);
    vector<int> primes;    
    rep(x,2,n) {
        if (is_prime[x]) {
            primes.push_back(x);
            for (int y = x*x; y <= n; y += x) {
                is_prime[y] = false;
            }
        }
    }
    return primes;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    vector<int> primes = get_primes_up_to((int)ceil(sqrt(1e9)));
    int t; cin >> t;
    while (t--) {
        int n,m; cin >> m >> n;
        if (m == 1) m++;
        rep(x,m,n) {
            if ((x & 1) == 0) continue;
            bool isprime = true;
            for (int p : primes) {
                if (p*p > x) break;
                if (x % p == 0) {
                    isprime = false;
                    break;
                }
            }
            if (isprime) cout << x << '\n';
        }
        if (t) cout << '\n';
    }
    return 0;
}