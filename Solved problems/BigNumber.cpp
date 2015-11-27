#include <cstdio>
#include <cmath>
using namespace std;
#define MAX_SIZE 10000000

double accum_logs[MAX_SIZE + 1];

int main() {

	accum_logs[0] = 0;
	for(int i = 1; i <= MAX_SIZE; ++i)
		accum_logs[i] = accum_logs[i-1] + log10(i);

	int n;
	scanf("%d",&n);
	while(n--) {
		int x;
		scanf("%d",&x);
		int n_digits = (int)floor(accum_logs[x])+1;
		printf("%d\n",n_digits);
	}
	return 0;
}
