//=============================================
// Sieve of Eratosthenes (all primes up to N)
//=============================================
#include <vector>
#include <cmath>
void collect_primes_up_to(int n, vector<int>& primes) {
	vector<bool> isPrime(n + 1, true);
	int limit = (int) floor(sqrt(n));
	for (int i = 2; i <= limit; ++i)
		if (isPrime[i])
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = false;
	for (int i = 2; i <= n; ++i)
		if (isPrime[i])
			primes.push_back(i);
}


//====================================
// Prime Factorization of Factorials
//====================================
// source: http://mathforum.org/library/drmath/view/67291.html
int N = 9999;
int pcount[N];
vector<int> primes;
collect_primes_up_to(N,primes);
int number = 12312; //the number we want the prime factorization from
for (int i = 0; i < (int)primes.size() && primes[i] <= N; ++i) {
	int p = primes[i];
	pcount[p] = 0;
	int n = number;
	while ((n /= p) > 0)
		pcount[p] += n;
}