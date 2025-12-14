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

vector<ll> factors;

pair<int, vector<ll>> search(int i, ll sum) {
	rep(_,0,i) cout << "  ";
	cout << "search(" << i << ", " << sum << ")\n";
	ll prod = 1;
	int min_count = INT_MAX;
	vector<ll> group;
	for (int j = i; j < factors.size(); ++j) {
		prod *= factors[j];
		if (prod > sum) break;
		if (j + 1 == factors.size()) {
			if (prod == sum) {
				min_count = 1;
				group = {prod};
				break;
			}
		} else {
			rep(_,0,i) cout << "  ";
			cout << "  prod: " << prod << "\n";
			auto res = search(j+1, sum - prod);
			if (res.ff != INT_MAX) {
				if (res.ff + 1 < min_count) {
					min_count = res.ff + 1;
					group.push_back(prod);
					for (ll f : res.ss) group.push_back(f);
				}
			}
		}
	}
	return {min_count, group};
}

// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    vector<ll> primes = get_primes_up_to(1000000);
    int T; cin >> T;
    rep(t, 1, T+1) {
        ll P; cin >> P;
        factors = trial_division_precomp(P, primes);
        ll sum = 0;
        for (ll f : factors) sum += f;
        if (sum > 41) {
            cout << "Case #" << t << ": -1\n";
            continue;
        }
		// while (sum < 41) {
		// 	factors.push_back(1);
		// 	++sum;
		// }
		sort(factors.begin(), factors.end());
		// try all permutations of factors
		int min_count = INT_MAX;
		vector<ll> group;
		do {
			cout << "------------------\n";
			cout << "factors: ";
			for (ll f : factors) cout << f << " ";
			cout << "\n";
			auto res = search(0, 41);
			// cout << "res.ff: " << res.ff << "\n";
			// cout << "res.ss: ";
			// for (ll f : res.ss) cout << f << " ";
			// cout << "\n";
			if (res.ff != INT_MAX) {
				if (res.ff < min_count) {
					min_count = res.ff;
					group = res.ss;
				}
			}
		} while (next_permutation(factors.begin(), factors.end()));
		assert (min_count != INT_MAX);
		ll group_sum = 0;
		for (ll f : group) group_sum += f;
		cout << "group_sum: " << group_sum << "\n";
		assert(group_sum <= 41);
        cout << "Case #" << t << ": " << group.size();
        for (ll f : group) cout << " " << f;
        cout << "\n";
    }
    return 0;
}

