#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int N, K;
int x[1000];
int w[1000];
long long f[1000];
long long g[1000];
long long dp[1001][1000];

typedef struct {
	long long x;
	long long y;
} point;

point lowerHull[1000];
int lhcount;

long long binarySearch(int slope) {

	int l = 0, r = lhcount - 1;

	while (l < r) {
		int m = (l + r) >> 1;
		if (m == r
				|| lowerHull[m + 1].x * slope + lowerHull[m + 1].y
						>= lowerHull[m].x * slope + lowerHull[m].y) {
			r = m;
		} else {
			l = m + 1;
		}
	}
	long long ans = lowerHull[r].x * slope + lowerHull[r].y;
	return ans;
}

void updateLowerHull(point &pt) {
	if (lhcount < 2) {
		lowerHull[lhcount] = pt;
		lhcount++;
	} else {
		long long y2, x2, y1, x1, y0, x0;
		x2 = pt.x;
		y2 = pt.y;
		x1 = lowerHull[lhcount - 1].x;
		y1 = lowerHull[lhcount - 1].y;
		x0 = lowerHull[lhcount - 2].x;
		y0 = lowerHull[lhcount - 2].y;

		if ((y2 - y1) * (x1 - x0) <= (y1 - y0) * (x2 - x1)) {
			lowerHull[lhcount] = pt;
			lhcount++;
		} else {
			lowerHull[lhcount - 1].x = x2;
			lowerHull[lhcount - 1].y = y2;

			while (lhcount > 2) {

				x2 = lowerHull[lhcount - 1].x;
				y2 = lowerHull[lhcount - 1].y;
				x1 = lowerHull[lhcount - 2].x;
				y1 = lowerHull[lhcount - 2].y;
				x0 = lowerHull[lhcount - 3].x;
				y0 = lowerHull[lhcount - 3].y;

				if ((y2 - y1) * (x1 - x0) > (y1 - y0) * (x2 - x1)) {
					lhcount--;
					lowerHull[lhcount - 1].x = x2;
					lowerHull[lhcount - 1].y = y2;
				} else {
					break;
				}

			}
		}
	}
}

int main() {

	memset(dp, 0, sizeof(dp));

	while (scanf("%d %d", &N, &K) == 2) {

		for (int i = 0; i < N; ++i) {
			scanf("%d %d", &x[i], &w[i]);
		}

		f[0] = w[0];
		g[0] = (long long) x[0] * w[0];
		for (int i = 1; i < N; ++i) {
			f[i] = f[i - 1] + w[i];
			g[i] = g[i - 1] + (long long) x[i] * w[i];
		}

		for (int i = 0; i < N; ++i) {
			dp[1][i] = x[i] * f[i] - g[i];
		}
		for (int k = 2; k <= K; ++k) {
			lhcount = 0;
			point pt;

			for (int i = k - 1; i < N; ++i) {

				pt.x = -f[i - 1];
				pt.y = g[i - 1] + dp[k - 1][i - 1];

				updateLowerHull(pt);

				dp[k][i] = binarySearch(x[i]) + x[i] * f[i] - g[i];
			}
		}
		printf("%lld\n", dp[K][N - 1]);
	}
	return 0;
}
