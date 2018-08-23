#include <cstdio>
#include <cstring>
using namespace std;

int count[5001];
char buff[10];
int dcounts[10];

int main() {

	count[0] = 0;
	count[1] = 1;
	for(int i = 2; i <= 5000; ++i) {
		count[i] = count[i-1];
		sprintf(buff,"%d",i);
		int length = strlen(buff);
		memset(dcounts,0,sizeof dcounts);

		bool repeats = false;
		for(int j = 0; j < length; ++j) {
			int d = buff[j]-'0';
			if(++dcounts[d] > 1) {
				repeats = true;
				break;
			}
		}

		if(!repeats)
			count[i]++;
	}

	int n,m;
	while(scanf("%d %d",&n,&m) == 2) {
		int ans = count[m] - count[n-1];
		printf("%d\n",ans);
	}

	return 0;
}
