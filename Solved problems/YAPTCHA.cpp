#include <cstdio>
#include <cmath>
#include <vector>
using namespace std;

const int MAXN = 1000000;
const int MAXNK = 3 * MAXN + 7;

vector<bool> isprime(MAXNK + 1, true);
vector<int> prime_counts(MAXN + 1, 0);

void set_primes() {
	int limit = (int) floor(sqrt(MAXNK));
	for (int i = 2; i <= limit; ++i)
		if (isprime[i])
			for (int j = i * i; j <= MAXNK; j += i)
				isprime[j] = false;
}
void compute_prime_counts() {
	for (int n = 1; n <= MAXN; ++n) {
		prime_counts[n] = prime_counts[n - 1];
		if (isprime[3 * n + 7])
			prime_counts[n]++;
	}
}

int main() {
	set_primes();
	compute_prime_counts();
	int t, n;
	scanf("%d", &t);
	while (t-- > 0) {
		scanf("%d", &n);
		printf("%d\n", prime_counts[n]);
	}
	return 0;
}
