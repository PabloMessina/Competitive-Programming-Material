#include <cstdio>
#include <cmath>
using namespace std;

double F1(double L) {
	double L_1toL = pow(L - 1, L);
	return (L_1toL * (L * L - 2 * L - 1) + 1) / ((L_1toL - 1) * (L - 2));
}

double F2(int L) {
	long long numerator = 0;
	long long denominator = 0;

	long long coef = 1;
	for (int k = 1; k < L; ++k) {
		coef *= L - k;
		numerator += k * coef;
		denominator += coef;
	}

	return numerator / (double) denominator;

}

double F3(int L) {
	long long numerator = 0;
	long long denominator = 0;

	long long coef = 1;
	for (int k = 2; k < L; ++k) {
		coef *= L - k;
		numerator += (k + 1) * coef;
		denominator += coef;
	}
	return numerator / (double) denominator;
}

double f1[15];
double f2[15];
double f3[15];

int main() {
	int L;

	for (L = 3; L <= 15; ++L) {
		f1[L] = F1((double) L);
		f2[L] = F2(L);
		f3[L] = F3(L);
	}

	while (true) {
		scanf("%d", &L);
		if (L == 0)
			break;
		printf("%.4f %.4f %.4f\n", f1[L], f2[L], f3[L]);
	}

	return 0;
}