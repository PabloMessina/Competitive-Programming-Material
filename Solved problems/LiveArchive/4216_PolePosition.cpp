#include <cstdio>
#include <cstring>
using namespace std;

#define FOR(i,first,n) for(int i=first; i < n; ++i)

int standings[1005];
int main() {
	int n;
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;

		bool valid = true;
		memset(standings, 0, sizeof(standings));

		FOR(i,0,n) {
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
			printf("%d", standings[0]);
			FOR(i,1,n) printf(" %d", standings[i]);
			puts("");
		} else {
			printf("-1\n");
		}
	}
	return 0;
}
