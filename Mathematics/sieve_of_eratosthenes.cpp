#define rep(i,a,b) for(int i=a;i<b;++i)
//=============================================
// Sieve of Eratosthenes (all primes up to N)
//=============================================
// O ( n log log n )
vector<int> get_primes_up_to(int n) {
	vector<bool> is_prime(n + 1, true);
	int limit = floor(sqrt(n));
	rep (i,2,limit+1)
		if (is_prime[i])
			for (int j = i*i; j <= n; j += i)
				is_prime[j] =  false;
	vector<int> primes;
	rep(i,2,n) if (is_prime[i]) primes.push_back(i);
	return primes;
}