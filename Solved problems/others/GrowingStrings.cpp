#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;

#define MAX_N 10000
#define MAX_L 1010000
#define B 261

typedef unsigned long long ull;

int n;
ull powB[MAX_L];
ull hash[MAX_L];
char s[MAX_L];
int pos[MAX_L];
int length[MAX_L];
int sindexes[MAX_N];
int ancestorCount[MAX_N];

ull getHash(int i, int j) {
	ull h = hash[j];
	if (i)
		h -= hash[i - 1] * powB[j - i + 1];
	return h;
}

bool cmpByLength(const int& i, const int& j) {
	return length[i] > length[j];
}

bool isSubstring(int source, int target) {

//	printf("====> isSubstring()\n");
	int lt = length[target];
	int pt = pos[target];
	ull ht = getHash(pt, pt + lt - 1);

	int ls = length[source];
	int ps = pos[source];

//	printf("\tsource = %.*s\n", ls, s + ps);
//
//	printf("\ttarget = %.*s\n", lt, s + pt);
//	printf("\ttarget hash = %llu\n", ht);

	for (int i = 0; i + lt <= ls; ++i) {

//		printf("\t\tsubstring = %.*s\n", lt, s + ps + i);

		ull h = getHash(ps + i, ps + i + lt - 1);

//		printf("\t\tsubhash = %llu\n", h);

		if (h == ht && strncmp(s + ps + i, s + pt, lt) == 0)
			return true;
	}
	return false;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

//pre-compute powers of B
	powB[0] = 1;
	for (int i = 1; i <= MAX_L; ++i)
		powB[i] = powB[i - 1] * B;

	while (true) {

		scanf("%d", &n);
		if (n == 0)
			break;

		//store all input strings in a single array
		int p = 0;
		for (int i = 0; i < n; ++i) {
			scanf("%s", s + p);
			pos[i] = p;
			length[i] = strlen(s + p);
			p += length[i];
			sindexes[i] = i;
		}

		//compute rolling hashes
		hash[0] = s[0];
		for (int i = 1; i < p; ++i)
			hash[i] = hash[i - 1] * B + s[i];

		//sort decreasingly by length
		sort(sindexes, sindexes + n, cmpByLength);

		memset(ancestorCount, 0, sizeof ancestorCount);

		//find the longest path
		int longestPath = 1;
		for (int i = 0; i < n - 1; ++i) {
			int i1 = sindexes[i];
//			printf("%.*s\n", length[i1], s + pos[i1]);
			for (int j = i + 1; j < n; ++j) {
				int i2 = sindexes[j];
				if (length[i2] == length[i1])
					continue;
//				printf("\t%.*s", length[i2], s + pos[i2]);
				if (isSubstring(i1, i2)) {
					if (ancestorCount[i2] < ancestorCount[i1] + 1) {
						ancestorCount[i2] = ancestorCount[i1] + 1;
						longestPath = max(longestPath, ancestorCount[i2] + 1);
					}
//					printf("\tFOUND!!!!!!\n");
				}
//				printf("\n");
			}
		}

		printf("%d\n", longestPath);

	}

	return 0;
}
