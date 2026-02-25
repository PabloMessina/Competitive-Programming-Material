// tags: math, prime factorization, trial division, sieve of eratosthenes
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
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
vector<ll> trial_division_precomp(ll n, vector<ll>& primes) {
	vector<ll> factors;
	for (ll d : primes) {
		if (d*d > n) break;
		while (n % d == 0) {
			factors.push_back(d);
			if ((n /= d) == 1) return factors;
		}
	}
	if (n > 1) factors.push_back(n);
	return factors;
}

vector<ll> get_primes_up_to(ll n) {
	vector<bool> is_prime(n + 1, true);
	ll limit = floor(sqrt(n));
	rep (i,2,limit+1)
		if (is_prime[i])
			for (ll j = i*i; j <= n; j += i)
				is_prime[j] =  false;
	vector<ll> primes;
	rep(i,2,n) if (is_prime[i]) primes.push_back(i);
	return primes;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string X; cin >> X;
    int prefix_length;
    ll prefix_value;
    if (X.size() > 10) {
        prefix_length = 10;
        prefix_value = stoll(X.substr(0, 10));
    } else {
        prefix_length = X.size();
        prefix_value = stoll(X);
    }

    vector<ll> primes = get_primes_up_to(floor(sqrt(prefix_value + 100)));
    vector<ll> factors = trial_division_precomp(prefix_value, primes);
    map<ll,int> factor_counts;
    for (ll f : factors) factor_counts[f]++;
    int num_zeroes = X.size() - prefix_length;
    if (num_zeroes > 0) {
        factor_counts[2] += num_zeroes;
        factor_counts[5] += num_zeroes;
    }
    cout << factor_counts.size() << '\n';
    for (auto [f, count] : factor_counts) {
        cout << f << " " << count << '\n';
    }
    return 0;
}