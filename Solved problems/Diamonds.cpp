#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int X[10000];
int Y[10000];
int Rmin[10000];
int Pmax[200];
int MD[10000]; //manhattan distance

int main() {

	int R, C;
	scanf("%d %d", &R, &C);
	int n = 0;
	int x, y;
	while (scanf("%d %d", &x, &y) == 2) {
		if (x < 0 || x >= C || y < 0 || y >= R)
			continue;
		X[n] = x;
		Y[n] = y;
		///printf("x = %d, y = %d\n",x,y);
		n++;
	}
	//printf("n = %d\n",n);

	memset(Rmin, 0, sizeof(Rmin));
	memset(Pmax, 0, sizeof(Pmax));

	for (int i = 0; i < C; ++i) {
		for (int j = 0; j < R; ++j) {

			for (int k = 0; k < n; ++k)
				MD[k] = abs(i - X[k]) + abs(j - Y[k]);
			sort(MD, MD + n);

			for (int k = 0; k < n; ++k) {
				int base = k;
				while (k + 1 < n && MD[k + 1] == MD[base])
					++k;
				int r = max(MD[base], 1);
				for (int p = base; p <= k; ++p)
					Rmin[p+1] = max(Rmin[p+1], r);
				Pmax[r] = max(Pmax[r], k + 1);
			}
		}
	}

	for (int r = 1; r <= 200; ++r)
		Pmax[r] = max(Pmax[r], Pmax[r - 1]);

	printf("Pmin  Rmin(Pmin)  Pmax(Pmin)\n");
	for (int pmin = 1; pmin <= n; ++pmin) {
		if (pmin + 1 <= n && Rmin[pmin] == Rmin[pmin + 1])
			continue;
		printf("%4d  %10d  %10d\n", pmin, Rmin[pmin], Pmax[Rmin[pmin]]);
	}

	return 0;
}
