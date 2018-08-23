#include <cstring>
#include <cstdio>
#include <vector>
using namespace std;

#define LSOne(S) (S & (-S))

int ft[20000+5];
int ans[20000+5];

int rsq(int b) {
	int sum = 0; for (; b; b -= LSOne(b)) sum += ft[b];
	return sum;
}

void adjust(int k, int v, int size) {
   for (; k < size; k += LSOne(k)) ft[k] += v;
}

int binSearch(int l, int r, int k) {
	while(l<r) {
		int imid = (l+r)>>1;
		if(rsq(imid) < k) {
			l = imid + 1;
		} else {
			r = imid;
		}
	}
	return l;
}

int main() {
	int t,n,size;
	scanf("%d",&t);
	while(t-->0) {
		scanf("%d",&n);
		size = n+1;
		memset(ft,0,sizeof(int)*size);
		for(int k = 1; k <= n; ++k) {
			adjust(k,1,size);
		}
		int freeSpaces = n;
		int index = 0;
		for(int i = 1; i<= n; ++i) {
			int k = (rsq(index)+i)%freeSpaces + 1;
			index = binSearch(k,n,k);
			adjust(index,-1,size);
			ans[index]=i;
			freeSpaces--;
		}
		for(int i=1;i<=n; ++i) {
			if(i==1)
				printf("%d",ans[i]);
			else
				printf(" %d",ans[i]);
		}
		printf("\n");
	}
	return 0;
}
