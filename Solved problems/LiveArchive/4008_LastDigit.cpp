// tags: math, sieve of eratosthenes, binary modular exponentiation,
// prime factorization of factorials
#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
using namespace std;

#define MAXN 1000000

char buffer[MAXN + 1];
int counts[26];
vector<bool> isPrime(MAXN + 1, true);
vector<int> primes;
int pcount[MAXN + 1];

//Sieve of Eratosthenes
void collect_primes_up_to(int n) {
	int limit = (int) floor(sqrt(n));
	for (int i = 2; i <= limit; ++i)
		if (isPrime[i])
			for (int j = i * i; j <= n; j += i)
				isPrime[j] = false;
	for (int i = 2; i <= n; ++i)
		if (isPrime[i])
			primes.push_back(i);
}

//binary modular exponentiation
int mod_pow(int b, int e, int m) {
	if (e == 1)
		return b % m;
	int he = e / 2;
	int x = mod_pow(b, he, m);
	x = (x * x) % m;
	if (e % 2 == 1)
		x = (x * b) % m;
	return x;
}

int main() {

	collect_primes_up_to(MAXN);

	while (gets(buffer) != NULL) {

		//read string and count repeated characters
		memset(counts, 0, sizeof counts);
		int length = strlen(buffer);
		for (int i = 0; i < length; ++i)
			counts[buffer[i] - 'a']++;

		//add prime factors of length!
		for (int i = 0; i < (int)primes.size() && primes[i] <= length; ++i) {
			int p = primes[i];
			pcount[p] = 0;
			int n = length;
			while ((n /= p) > 0)
				pcount[p] += n;
		}

		//remove prime factors of repeated letters
		for (int i = 0; i < 26; ++i) {
			int count = counts[i];
			if (count > 1) {
				for (int j = 0; j < (int)primes.size() && primes[j] <= count; ++j) {
					int p = primes[j];
					int n = count;
					while ((n /= p) > 0)
						pcount[p] -= n;
				}
			}
		}

		//remove 10s
		if (length >= 5) {
			int m = min(pcount[2], pcount[5]);
			pcount[2] -= m;
			pcount[5] -= m;
		}

		//compute multiplication mod 10
		int x = 1;
		for (int i = 0; i < (int)primes.size() && primes[i] <= length; ++i) {
			int p = primes[i];
			if (pcount[p] > 0)
				x = (x * mod_pow(p, pcount[p], 10)) % 10;
		}
		printf("%d\n", x);
	}

}
