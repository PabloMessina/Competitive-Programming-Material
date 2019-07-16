//=====================
// Prime Factorization
//=====================
// reference: https://cp-algorithms.com/algebra/factorization.html

// method 1: trial division
// complexity: ~ O( sqrt(n) + log(n) )
vector<int> trial_division(int n) {
	vector<int> factors;
	for (int d = 2; d*d <= n; d++) {
		while (n % d == 0) {
			factors.push_back(d);
			if ((n /= d) == 1) return factors;
		}
	}
	if (n > 1) factors.push_back(n);
	return factors;
}

// method 2: precomputed primes
// complexity: ~ O( sqrt(n)/log(sqrt(n)) + log(n) )
//   + time of precomputing primes
vector<int> trial_division_precomp(int n, vector<int>& primes) {
	vector<int> factors;
	for (int d : primes) {
		if (d*d > n) break;
		while (n % d == 0) {
			factors.push_back(d);
			if ((n /= d) == 1) return factors;
		}
	}
	if (n > 1) factors.push_back(n);
	return factors;
}

//====================================
// Prime Factorization of Factorials
//====================================
// references:
// http://mathforum.org/library/drmath/view/67291.html
// https://janmr.com/blog/2010/10/prime-factors-of-factorial-numbers/
#define umap unordered_map
umap<int,int> factorial_prime_factorization(int n, vector<int>& primes) {
	umap<int,int> prime2exp;
	for (int p : primes) {
		if (p > n) break;
		int e = 0;
		int tmp = n;
		while ((tmp /= p) > 0) e += tmp;
		if (e) prime2exp[p] = e;
	}
	return prime2exp;
}