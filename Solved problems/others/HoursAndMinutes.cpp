#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

bool exists[361];

int main() {

	//setvbuf(stdout, NULL, _IONBF, 0);

	memset(exists, false, sizeof exists);

	for (int c = 0; c < 720; ++c) {
		int m = c % 60;
		int h = (c / 60) % 12;
		int a_m = m * 6;
		int a_h = h * 30;
		int d = abs(a_m - a_h);
		exists[min(360 - d, d)] = true;
	}

	int a;
	while (scanf("%d", &a) == 1) {
		if (exists[a])
			printf("Y\n");
		else
			printf("N\n");
	}

	return 0;
}