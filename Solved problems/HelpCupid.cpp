#include <cstdio>
#include <algorithm>
using namespace std;

int N;
int T[1005];

int main() {

	while (scanf("%d", &N) == 1) {
		for (int i = 0; i < N; ++i)
			scanf("%d", &T[i]);
		sort(T, T + N);

		int sum1 = 0;
		for (int i = 0; i + 1 < N; i += 2) {
			int dt = T[i + 1] - T[i];
			sum1 += min(dt, 24 - dt);
		}

		int dt2 = (T[N - 1] - T[0]);
		int sum2 = min(dt2, 24 - dt2);
		for (int i = 1; i + 1 < N; i += 2) {
			int dt = T[i + 1] - T[i];
			sum2 += min(dt, 24 - dt);
		}

		printf("%d\n", min(sum1, sum2));

	}

	return 0;
}
