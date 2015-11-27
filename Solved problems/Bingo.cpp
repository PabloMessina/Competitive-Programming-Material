#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

bool canGenerate[91];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	loop: while (true) {

		int n, b;
		scanf("%d %d", &n, &b);
		if (n == 0 && b == 0)
			break;

		vector<int> balls;
		for (int i = 0; i < b; ++i) {
			int ball;
			scanf("%d", &ball);
			balls.push_back(ball);
		}

		memset(canGenerate, 0, sizeof canGenerate);

		for (int i = 0; i < b - 1; ++i)
			for (int j = i + 1; j < b; ++j)
				canGenerate[abs(balls[i] - balls[j])] = true;

		for (int i = 1; i <= n; ++i)
			if (!canGenerate[i]) {
				printf("N\n");
				goto loop;
			}

		printf("Y\n");

	}

	return 0;
}
