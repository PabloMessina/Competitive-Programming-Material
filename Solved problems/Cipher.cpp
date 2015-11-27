#include <cstring>
#include <cstdio>
#include <algorithm>
using namespace std;

int toshift[201];
int shifters[201][201];
int cicles[201];
char buffer1[201];
char buffer2[201];
char inputBuffer[1000];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

//
//	int a[200];
//	for(int i = 0; i < 100; ++i)
//		a[i]=i+1;
//	random_shuffle(&a[0],&a[99]);
//
//	for(int i=0;i < 100;++i)
//		printf("%d ",a[i]);

	while (true) {

		int n;
		scanf("%d", &n);
		//		printf("n = %d\n",n);
		if (n == 0)
			break;

		for (int i = 0; i < n; ++i) {
			scanf("%d", &toshift[i]);
			toshift[i]--;
			shifters[0][i] = i;
		}

		memset(cicles, 0, sizeof(cicles));

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j < n; ++j) {
				int nextIndex = toshift[j];
				if ((shifters[i][nextIndex] = shifters[i - 1][j]) == nextIndex
						&& cicles[nextIndex] == 0) {
					cicles[nextIndex] = i;
				}
			}
		}

		//debug
//			for(int i = 0; i < n; ++i) {
//				printf("%d\t",cicles[i]);
//			}
//			printf("\n");
//			for(int i = 0; i <= n; ++i) {
//				printf("i == %d: ",i);
//				for(int j = 0; j < n; ++j) {
//					printf("%d\t",shifters[i][j]);
//				}
//				printf("\n");
//			}
//			printf("------------\n");

		while (true) {
			long long k;
			scanf("%lld", &k);
			if (k == 0)
				break;

			getchar();

			char c;
			int index = 0;
			while ((c = getchar()) != '\n') {
				//				printf("c = %c",c);
				//				printf("index = %d\n", index);
				buffer1[index] = c;
				index++;
			}
			//index--;
			while (index < n) {
				buffer1[index] = ' ';
				index++;
			}
			buffer1[n] = '\0';

			//			printf("k = %ld, n = %d, buffer1 = ||%s||\n",k,n,buffer1);
			//			for(int i = 0; i <= n; ++i) {
			//				printf("-(%d_%c)-",buffer1[i],buffer1[i]);
			//			}
			//			printf("\n");
			//			printf("k = %ld\n",k);
			//			printf("s = %s\n",buffer1);

			//			return 0;
			//			string line;
			//			std::getline(cin, line);
			//			memcpy(buffer1, line.c_str(), line.size());
			//			memset(buffer1 + line.size(), ' ', n - line.size());
			//			printf("buffer = ||%s||\n",buffer1);

			for (int j = 0; j < n; ++j)
				buffer2[j] = buffer1[shifters[k % cicles[j]][j]];
			for (int i = 0; i < n; ++i)
				printf("%c", buffer2[i]);
			printf("\n");

//			printf("##");
//			for(int i = 0; i < n; ++i)
//				printf("(%d)",buffer2[i]);
//			printf("\n");
		}
		printf("\n");
	}

	return 0;
}
