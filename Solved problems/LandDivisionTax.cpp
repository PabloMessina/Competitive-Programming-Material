/*
 * DP
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long int ll;

int N;
float F;
int areas[205];
ll DP[202][202];
ll Acc[202];
ll infinity = 99999999;

ll getArea(int i, int j) {
	if (i <= j)
		return Acc[j] - ((i > 0) ? Acc[i - 1] : 0);
	return Acc[j] + Acc[N - 1] - Acc[i - 1];
}

int main() {

	while (true) {
		scanf("%d %f", &N, &F);
		if (N == 0)
			break;
		// read areas
		for (int i = 0; i < N; ++i) {
			scanf("%d", &areas[i]);
			Acc[i] = areas[i];
			if (i > 0)
				Acc[i] += Acc[i - 1];
		}

//		printf("-----------------------------\n");
//		printf("-----------------------------\n");

		if (N == 1) {
			printf("0.00\n");
			continue;
		}

		for (int i = 0; i < N; ++i)
			DP[i][i] = 0;

		for (int l = 2; l < N; ++l) {
			for (int i = 0; i < N; ++i) {
				int j = (i + l - 1) % N;

//				printf("l = %d, i = %d, j = %d\n", l, i, j);

				int minv = infinity;

				for (int ii = i; ii < i + l - 1; ++ii) {
					int k = ii % N;

					ll area_ik = getArea(i, k);
					ll area_k1j = getArea((k + 1) % N, j);
					ll dp_ik = DP[i][k];
					ll dp_k1j = DP[(k + 1)%N][j];
					ll v = max(area_ik, area_k1j) + dp_ik + dp_k1j;
//					printf(
//							"\tk=%d, area_ik=%lld, area_k1j=%lld,dp[%d][%d]=%lld,dp[%d][%d]=%lld,v=%lld\n",
//							k, area_ik, area_k1j, i, k, dp_ik, (k + 1)%N, j, dp_k1j,
//							v);

					if (minv > v)
						minv = v;
				}

				DP[i][j] = minv;
//				printf("\t--\n\tDP[%d][%d] = %lld\n",i,j,DP[i][j]);
			}
		}

		ll mincost = infinity;
		for (int i = 0; i < N - 1; ++i) {
			for (int j = i + 1; j < N; ++j) {
				ll area_ij = Acc[j] - Acc[i];
				ll v = max(area_ij, Acc[N - 1] - area_ij) + DP[i + 1][j]
						+ DP[(j + 1) % N][i];
				if (mincost > v)
					mincost = v;
			}
		}
		float ans = mincost * F;

//		printf("mincost = %lld, F = %f, ans = %f\n", mincost, F, ans);
//
//		printf("Acc:\n");
//		for (int i = 0; i < N; ++i)
//			printf("%lld ", Acc[i]);
//		printf("\n");
//
//		printf("DP:\n");
//		for (int i = 0; i < N; ++i) {
//			for (int j = 0; j < N; ++j) {
//				printf("%lld ", DP[i][j]);
//			}
//			printf("\n");
//		}

		printf("%.2f\n", ans);
	}

	return 0;
}

