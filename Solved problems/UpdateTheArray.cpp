#include <cstdio>
#include <cstring>
using namespace std;

int main() {

	int vals[10001];
	int t;
	scanf("%d", &t);
	while (t-- > 0) {
		int n, u;
		scanf("%d %d",&n,&u);
		memset(vals,0,(n+1)*sizeof(int));
		while(u-->0) {
			int l, r, val;
			scanf("%d %d %d",&l, &r, &val);
			vals[l] += val;
			vals[r+1] -= val;
		}
		int div = 0;
		for(int i = 0; i < n; ++i) {
			div+=vals[i];
			vals[i] = div;
		}
		int q;
		scanf("%d",&q);
		for(int i = 0; i < q; ++i) {
			int index;
			scanf("%d",&index);
			printf("%d\n",vals[index]);
		}
	}
	return 0;
}