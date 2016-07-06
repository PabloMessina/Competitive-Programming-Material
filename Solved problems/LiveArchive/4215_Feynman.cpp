#include <cstdio>
#include <cstring>
using namespace std;

int memo[101];

void fill_memo() {
	memset(memo,0,sizeof(memo));
	for(int n = 1; n <= 100; ++n) {
		int sum = 0;
		for(int i = 0; i < n; ++i) {
			sum += (n-i)*(n-i);
		}
		memo[n] = sum;
	}
}

int main() {

	fill_memo();

	while (true) {
		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		printf("%d\n", memo[n]);
	}
	return 0;
}
