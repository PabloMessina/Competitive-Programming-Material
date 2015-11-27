#include <cstdio>
using namespace std;

int choice[101][200];
int dp[101][200];
int MOD;
char answer[101];

int findNumber(int i, int remainder) {
	if (remainder == 0)
		return i;

	if (i == 100)
		return 999999;

	if (dp[i][remainder] != -1)
		return dp[i][remainder];

	int a = findNumber(i + 1, (remainder * 10) % MOD);
	int b = findNumber(i + 1, (remainder * 10 + 1) % MOD);
	if (a < b)
		choice[i][remainder] = 0;
	else
		choice[i][remainder] = 1;

	return dp[i][remainder] = (a < b) ? a : b;

}

int main() {
	while (true) {
		scanf("%d", &MOD);
		if (MOD == 0)
			break;

		for (int i = 1; i <= 100; ++i)
			for (int j = 1; j < MOD; ++j)
				dp[i][j] = -1;

		int length = findNumber(1, 1 % MOD);

		answer[0] = '1';

		int rem = 1 % MOD;
		for (int i = 1; i < length; ++i) {
			answer[i] = '0' + choice[i][rem];
			rem = (rem * 10 + choice[i][rem]) % MOD;
		}
		answer[length] = '\0';
		printf("%s\n", answer);
	}
	return 0;
}