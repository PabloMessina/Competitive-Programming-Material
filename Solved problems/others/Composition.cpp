#include <cstdio>
#include <cstring>
using namespace std;
typedef unsigned long long int ull;
bool invalid[31];
ull counts[31];
int main() {
	int P;
	scanf("%d", &P);
	while (P-- > 0) {
		int d, n, m, k;
		scanf("%d %d %d %d", &d, &n, &m, &k);
		memset(invalid, 0, sizeof invalid);
		for (int i = m; i <= 30; i += k)
			invalid[i] = true;
		counts[1] = invalid[1] ? 0 : 1;
		for (int i = 2; i <= n; ++i) {
			counts[i] = 0;
			for (int j = 1; j < i; ++j) {
				if (invalid[i-j])
					continue;
				counts[i] += counts[j];
			}
			if (!invalid[i])
				counts[i]++;
		}
		printf("%d %llu\n", d, counts[n]);
	}
	return 0;
}
