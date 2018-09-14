#define MAXN 9999
#define umap unordered_map
#define rep(i,a,b) for(int i=a;i<=b;++i)

//=============================================
// Sieve of Eratosthenes (all primes up to N)
//=============================================
vector<int> get_primes_up_to(int n) {
	vector<bool> is_prime(n + 1, true);
	int limit = (int) floor(sqrt(n));
	rep (i,2,limit)
		if (is_prime[i])
			for (int j = i * i; j <= n; j += i)
				is_prime[j] = false;
	vector<int> primes;
	rep(i,2,n) if (is_prime[i]) primes.push_back(i);
	return primes;
}

//====================================
// Prime Factorization of Factorials
//====================================
// source: http://mathforum.org/library/drmath/view/67291.html
void factorial_prime_factorization(int x, umap<int,int>& counts) {
	static vector<int> primes = get_primes(MAXN);

	for (int p : primes) {
		if (p > x) break;
		int count = 0;
		int n = x;
		while ((n /= p) > 0)
			count += n;
		if (count) counts[p] = count;
	}	
}