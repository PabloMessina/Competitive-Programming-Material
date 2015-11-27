#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int m,n;
int row[100000+5];
int col[100000+5];
int dp[100000+5];

int main() {
	while(true) {
		scanf("%d %d",&m,&n);
		if(m == 0 && n == 0)
			break;

		for(int i = 0; i < m; ++i) {
			for(int j = 0; j < n; ++j) {
				scanf("%d",&row[j]);
			}
			dp[n] = 0;
			dp[n-1] = row[n-1];
			for(int j = n-2; j>= 0; --j) {
				dp[j] = std::max(dp[j+1],row[j]+dp[j+2]);
			}
			col[i] = dp[0];
		}
		dp[m] = 0;
		dp[m-1] = col[m-1];
		for(int i = m-2; i >= 0; --i) {
			dp[i] = std::max(dp[i+1],col[i]+dp[i+2]);
		}
		printf("%d\n",dp[0]);
	}
	return 0;
}
