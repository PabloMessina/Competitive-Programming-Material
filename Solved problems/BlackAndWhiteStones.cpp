#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

typedef long long int ll;

ll A, B;
char buffer[5005];
int bcounts[5005];

int main() {
	setvbuf(stdout, NULL, _IONBF, 0);

	while (scanf("%lld %lld %s", &A, &B, buffer) == 3) {
		int size = strlen(buffer);

		bcounts[0] = 0;

		for (int i = 0; i < size; ++i) {
			if (i > 0)
				bcounts[i] = bcounts[i - 1];
			if (buffer[i] == 'B')
				bcounts[i]++;
		}

		int totalBs = bcounts[size - 1];

		//0 B's
		if (totalBs == 0) {
			puts("0");
			continue;
		}

		int remaining = totalBs - bcounts[totalBs - 1];
		if (remaining == 0) { //already sorted
			puts("0");
			continue;
		}

		if (B == 0) { //no refund
			printf("%lld\n", A * remaining);
			continue;
		}

		int wi = totalBs - 1;
		int bi = totalBs;

		ll totalcost = 0;

		while (remaining-- > 0) {
			while (buffer[bi] != 'B')
				bi++;
			while (buffer[wi] != 'W')
				wi--;

			ll swap_cost = (bi - wi) * (A-B);

			if (swap_cost < A) {
				totalcost += swap_cost;
			} else {
				totalcost += A * (remaining + 1);
				break;
			}

			bi++;
			wi--;

		}

		printf("%lld\n", totalcost);

	}

	return 0;
}
