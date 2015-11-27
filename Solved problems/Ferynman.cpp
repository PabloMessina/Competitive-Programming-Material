#include <cstdio>
#include <cstring>
using namespace std;

int dp[101];

void fill_dp() {
	memset(dp,0,sizeof(dp));
	for(int n = 1; n <= 100; ++n) {
		int sum = 0;
		for(int i = 0; i < n; ++i) {
			sum += (n-i)*(n-i);
		}
		dp[n] = sum;
	}
}

int main() {

	fill_dp();

	while (true) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		printf("%d\n", dp[n]);
	}
	return 0;
}
