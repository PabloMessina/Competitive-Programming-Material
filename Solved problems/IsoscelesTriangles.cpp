#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

struct point {
	long long x;
	long long y;
};

int n;
long long distances[1000][1000];
point points[1000];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	point p;
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;

		for (int i = 0; i < n; ++i) {
			scanf("%lld %lld", &p.x, &p.y);
			points[i] = p;
		}

		int isoCount = 0;

		for (int i = 0; i < n; ++i) {
			for (int j = i+1; j < n; ++j) {
				point p1 = points[i];
				point p2 = points[j];
				distances[i][j] = (p1.x - p2.x) * (p1.x - p2.x)
						+ (p1.y - p2.y) * (p1.y - p2.y);
				distances[j][i] = distances[i][j];
			}
			distances[i][i] = 0;
			sort(distances[i],distances[i]+n);
			long long dist = -1;
			int count = 1;
			for(int j = 2; j < n; ++j) {
				if(distances[i][j] == distances[i][j-1]) {
					count ++;
					if(j == n-1) {
						isoCount += count * (count-1)/2;
					}
				} else {
					isoCount += count * (count-1)/2;
					count = 1;
				}
			}
		}

		printf("%d\n",isoCount);

	}

	return 0;
}
