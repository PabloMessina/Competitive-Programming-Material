#include <cstdio>
#include <algorithm>
using namespace std;

int W, D, A, K;

int coef_p1[10];
int coef_q1[10];
int coef_p2[10];
int coef_q2[10];

#define ITERATIONS 200
#define PARTITION_SIZE 10000

double y1[PARTITION_SIZE];
double y2[PARTITION_SIZE];

double f1(double x) {
	double num = coef_p1[0];
	double den = coef_q1[0];
	double _x = x;
	for (int i = 1; i <= K; ++i) {
		num += _x * coef_p1[i];
		den += _x * coef_q1[i];
		_x *= x;
	}
	return num / den;
}

double f2(double x) {
	double num = coef_p2[0];
	double den = coef_q2[0];
	double _x = x;
	for (int i = 1; i <= K; ++i) {
		num += _x * coef_p2[i];
		den += _x * coef_q2[i];
		_x *= x;
	}
	return num / den;
}

int main() {

	int i;

	while (scanf("%d %d %d %d", &W, &D, &A, &K) == 4) {

		for (i = 0; i <= K; ++i)
			scanf("%d", &coef_p1[i]);
		for (i = 0; i <= K; ++i)
			scanf("%d", &coef_q1[i]);
		for (i = 0; i <= K; ++i)
			scanf("%d", &coef_p2[i]);
		for (i = 0; i <= K; ++i)
			scanf("%d", &coef_q2[i]);

		double minD = 0;
		double maxD = D;
		double depth;

		double step = (double) W / PARTITION_SIZE;
		double half_step = step / 2;
		double x;

		double y1a, y1b, y2a, y2b, y1m, y2m;
		double sum;

		y1a = f1(0);
		y2a = f2(0);

		for (i = 0; i < PARTITION_SIZE; ++i) {
			x = step * i;
			y1b = f1(x + step);
			y1m = f1(x + half_step);
			y1[i] = (y1a + 4 * y1m + y1b) / 6;
			y1a = y1b;

			y2b = f2(x + step);
			y2m = f2(x + half_step);
			y2[i] = (y2a + 4 * y2m + y2b) / 6;
			y2a = y2b;
		}

		for (int j = 0; j < ITERATIONS; ++j) {
			depth = (maxD + minD) / 2;
			sum = 0;
			for (i = 0; i < PARTITION_SIZE; ++i)
				if (y1[i] > -depth)
					sum += (y1[i] - max(y2[i], -depth)) * step;
			if (sum < A)
				minD = depth;
			else
				maxD = depth;
		}

		printf("%.5f\n", depth);

	}

	return 0;
}
