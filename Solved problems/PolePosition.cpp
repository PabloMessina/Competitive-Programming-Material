#include <cstdio>
#include <cstring>
using namespace std;

int standings[1005];
int main() {
	int n;
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;

		bool valid = true;
		memset(standings, 0, sizeof(standings));

		for (int i = 0; i < n; ++i) {
			int carnumber;
			int shift;
			scanf("%d %d", &carnumber, &shift);

			if (!valid)
				continue;
			int j = i + shift;
			if (j < 0 || j >= n || standings[j] != 0) {
				valid = false;
				continue;
			}
			standings[j] = carnumber;
		}

		if (valid) {
			bool first = true;
			for (int i = 0; i < n; ++i) {
				if (first) {
					printf("%d", standings[i]);
					first = false;
				} else
					printf(" %d", standings[i]);
			}
			printf("\n");
		} else {
			printf("-1\n");
		}
	}
	return 0;
}
