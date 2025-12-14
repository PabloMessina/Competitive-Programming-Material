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

vector<ll> get_primes_up_to(int n) {
	vector<bool> is_prime(n + 1, true);
	ll limit = floor(sqrt(n));
	rep (i,2,limit+1)
		if (is_prime[i])
			for (int j = i*i; j <= n; j += i)
				is_prime[j] =  false;
	vector<ll> primes;
	rep(i,2,n) if (is_prime[i]) primes.push_back(i);
	return primes;
}

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
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    vector<ll> primes = get_primes_up_to(1000000);
    int T; cin >> T;
    rep(t, 1, T+1) {
        ll P; cin >> P;
        vector<ll> factors = trial_division_precomp(P, primes);
        ll sum = 0;
        for (ll f : factors) sum += f;
        if (sum > 41) {
            cout << "Case #" << t << ": -1\n";
            continue;
        }
        rep(i,0,41-sum) factors.push_back(1);
        cout << "Case #" << t << ": " << factors.size();
        for (ll f : factors) cout << " " << f;
        cout << "\n";
    }
    return 0;
}

