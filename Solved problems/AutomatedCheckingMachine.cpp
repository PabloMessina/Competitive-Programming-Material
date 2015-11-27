#include <cstdio>
using namespace std;

int c1[5];
int c2[5];

int main() {

	while (scanf("%d %d %d %d %d %d %d %d %d %d", &c1[0], &c1[1], &c1[2],
			&c1[3], &c1[4], &c2[0], &c2[1], &c2[2], &c2[3], &c2[4]) == 10) {

		bool valid = true;
		for (int i = 0; i < 5; ++i)
			if (c1[i] == c2[i]) {
				valid = false;
				break;
			}
		if (valid)
			puts("Y");
		else
			puts("N");
	}

	return 0;
}