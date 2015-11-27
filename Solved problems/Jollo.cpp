#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

bool used[53];
int p[3];
bool discarded[3];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		int x, y;

		scanf("%d %d %d %d %d", &p[0], &p[1], &p[2], &x, &y);
		if (!(p[0] || p[1] || p[2] || x || y))
			break;

		memset(used, 0, sizeof used);
		used[p[0]] = true;
		used[p[1]] = true;
		used[p[2]] = true;
		used[x] = true;
		used[y] = true;

		sort(p, p + 3);

//		for(int i = 0; i < 3; ++i)
//			printf("%d ",p[i]);
//		printf("\n");

		int x1 = min(x, y);
		int x2 = max(x, y);

		int count = 0;

		memset(discarded, 0, sizeof discarded);

		for (int i = 0; i < 3; ++i)
			if (x1 < p[i]) {
				discarded[i] = true;
				count++;
				break;
			}
		for (int i = 0; i < 3; ++i) {
			if (discarded[i])
				continue;
			if (x2 < p[i]) {
				discarded[i] = true;
				count++;
				break;
			}
		}

		if (count == 2) {
			printf("-1\n");
			continue;
		} else if (count == 0) {
			for (int i = 1; i <= 52; ++i) {
				if (used[i])
					continue;
				printf("%d\n", i);
				break;
			}
		} else {

			int pmax = -1;
			for (int i = 0; i < 3; ++i) {
				if (discarded[i])
					continue;
				pmax = max(pmax, p[i]);
			}

			int ans = -1;
			for (int i = pmax + 1; i <= 52; ++i) {
				if (used[i])
					continue;
				ans = i;
				break;
			}
			printf("%d\n", ans);
		}

	}

	return 0;
}
