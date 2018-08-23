#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

#define OPEN 1
#define CLOSE 2

typedef struct {
	int x;
	int y1;
	int y2;
	int type;
} vs;

bool compareVerticalSegments(const vs& a, const vs& b) {
	return a.x < b.x;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);


	int n;

	scanf("%d",&n);

	vector<vs> vss;

	vs vs;

	for(int i = 0; i < n; ++i) {
		int x1, y1, x2, y2;
		scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
		vs.x = x1;
		vs.y1 = y1;
		vs.y2 = y2-1;
		vs.type = OPEN;
		vss.push_back(vs);

		vs.x = x2;
		vs.type = CLOSE;
		vss.push_back(vs);
	}

//	printf("debug1\n");

	sort(vss.begin(), vss.end(), compareVerticalSegments);

//	printf("debug2\n");

	vector<int> counters;
	counters.assign(30005,0);

	int nonzeroLength = 0;
	int lastX = 0;
	int A = 0;

//	printf("debug3\n");

	for(unsigned i = 0; i < vss.size(); ++i) {
		vs = vss[i];
		A += (vs.x - lastX)*nonzeroLength;
		lastX = vs.x;

//		printf("i == %d, vs/ = (%d,%d,%d,%d)\n",i,vs.x,vs.y1,vs.y2,vs.type);

		if(vs.type == OPEN) {
//			printf("OPEN CASE\n");


//			printf("debug asldfjalsdf");


			for(int j = vs.y1; j <= vs.y2; ++j) {
//				printf("debug interno\n");
//				printf("\t j = %d, counters[j] = %d\n",j,counters[j]);
				if(counters[j] == 0)
					nonzeroLength++;
				counters[j]++;
			}
		} else {
//			printf("CLOSE CASE\n");
			for(int j = vs.y1; j <= vs.y2; ++j) {
//				printf("\tj = %d, counters[j] = %d\n",j,counters[j]);
				if(counters[j] == 1)
					nonzeroLength--;
				counters[j]--;
			}
		}
	}

//	printf("debug4\n");

	printf("%d\n",A);

	return 0;
}
