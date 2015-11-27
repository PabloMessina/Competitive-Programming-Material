#include <cstdio>
#include <cstring>
#include <vector>
#include <cstdlib>
using namespace std;

int n, k;
vector<vector<int> > indexes(26);
int lastIndexes[26];

int binSearch(const vector<int>& indexSet, int startIndex, int searchIndex, int& minDist) {
	int i = startIndex;
	int j = indexSet.size() - 1;
	while (i < j) {
		int imid = (i + j) >> 1;
		if (indexSet[imid] < searchIndex) {
			i = imid + 1;
		} else {
			j = imid;
		}
	}
	int ans = i;
	int mindist = abs(searchIndex - indexSet[i]);
	if (i - 1 >= 0) {
		int aux = abs(searchIndex - indexSet[i - 1]);
		if (aux < mindist) {
			mindist = aux;
			ans = i - 1;
		}
	}
	if (i + 1 < indexSet.size()) {
		int aux = abs(searchIndex - indexSet[i + 1]);
		if (aux < mindist)
			ans = i + 1;
	}
	minDist = mindist;
	return ans;
}

int main() {
	scanf("%d %d\n", &n, &k);
	for (int i = 0; i < k; ++i) {
		char c = getchar();
		indexes[c - 'a'].push_back(i);
	}
//	for(char c = 'a'; c <= 'z'; ++c) {
//		printf("%c: ",c);
//		for(int j = 0; j < indexes[c-'a'].size(); ++j) {
//			printf("%d ",indexes[c-'a'][j]);
//		}
//		printf("\n");
//	}
//	printf("---------------------\n");

	getchar();

	for (int i = 0; i < n; ++i) {
		char c;
		long long searchIndex = 0;
		long long F = 0;
		long long notFoundCount = 0;

		memset(lastIndexes,0,sizeof(lastIndexes));

		while ((c = getchar()) != '\n') {
//			printf("%c",c);
			int cindex = c - 'a';
			vector<int>& indexSet = indexes[cindex];
			if (indexSet.size() == 0)
				notFoundCount++;
			else {
				int minDist;
				lastIndexes[cindex] = binSearch(indexSet, lastIndexes[cindex],
						searchIndex, minDist);
				F+=minDist;
			}
			searchIndex++;
		}
//		printf("\n");
		F+=notFoundCount*searchIndex;
		printf("%lld\n",F);
	}

	return 0;
}