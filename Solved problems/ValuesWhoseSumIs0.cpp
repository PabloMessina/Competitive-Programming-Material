#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int A[4000];
int B[4000];
int C[4000];
int D[4000];
vector<int> c1(16000000);
vector<int> c2(16000000);

int main() {

	bool first = true;
	int cases;
	scanf("%d", &cases);
	while (cases--) {
		int n;
		scanf("%d", &n);
		for (int i = 0; i < n; ++i) {
			scanf("%d %d %d %d", &A[i], &B[i], &C[i], &D[i]);
		}
		for (int i = 0; i < n; ++i) {
			int offset = n * i;
			for (int j = 0; j < n; ++j) {
				c1[offset + j] = A[i] + B[j];
				c2[offset + j] = C[i] + D[j];
			}
		}
		int n2 = n * n;
		sort(c1.begin(), c1.begin() + n2);
		sort(c2.begin(), c2.begin() + n2);

//		printf("n2 = %d\n",n2);
//		for(int i = 0; i < n2; ++i)
//			printf("%d\t%d\n",c1[i],c2[i]);

		int i = 0, j = n2-1;
		long long count = 0;
		long long count1 = 1, count2 = 1;
		while (i <= n2 && j >= 0) {
			int sum = c1[i] + c2[j];
//			printf("sum = %d, c1[%d] = %d, c2[%d] = %d\n",sum,i,c1[i],j,c2[j]);
			if (sum == 0) {

				int val1 = c1[i];
				while (++i <= n2 && c1[i] == val1)
					count1++;

				int val2 = c2[j];
				while (--j >= 0 && c2[j] == val2)
					count2++;

				count += count1 * count2;

				count1 = 1;
				count2 = 1;

			} else if (sum > 0)
				j--;
			else
				i++;
		}
		if(first) first = false;
		else printf("\n");
		printf("%lld\n",count);

	}
	return 0;
}
