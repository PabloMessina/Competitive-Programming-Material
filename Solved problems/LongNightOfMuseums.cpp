#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define infinity 99999999

int N;
int mtime[20];
int mtime2[20];
int m2mtime[20][20];

int best_depth;
int max_depth;
int minTravelTime;

void bt(int mask, int timeleft, int curr_museum, int depth) {
	best_depth = max(best_depth, depth);
	if (best_depth == max_depth)
		return;
	for (int i = 0, b = 1; i < N; ++i, b <<= 1) {
		if (!(mask & b)) {
			if (timeleft >= mtime[i] + m2mtime[curr_museum][i])
				bt(mask | b, timeleft - mtime[i] - m2mtime[curr_museum][i], i,
						depth + 1);
		}
	}
}

int main() {

	while (true) {
		scanf("%d", &N);
		if (N == 0)
			break;

		//read museum times
		for (int i = 0; i < N; ++i) {
			scanf("%d", &mtime[i]);
			mtime2[i] = mtime[i];
		}
		sort(mtime2, mtime2 + N);

		//read museum to museum travel times
		minTravelTime = infinity;
		for (int i = 0; i < N; ++i) {
			for (int j = 0; j < N; ++j) {
				scanf("%d", &m2mtime[i][j]);
				if (i != j && minTravelTime > m2mtime[i][j])
					minTravelTime = m2mtime[i][j];
			}
		}

		//compute max_depth
		int timeleft = 420;
		if (mtime2[0] <= timeleft) {
			timeleft -= mtime2[0];
			max_depth = 1;
			for (int i = 1; i < N; ++i) {
				if ((timeleft -= (minTravelTime + mtime2[i])) < 0)
					break;
				max_depth++;
			}
		} else {
			max_depth = 0;
		}

		//run backtracking
		best_depth = 0;
		for (int i = 0; i < N; ++i) {
			if (420 >= mtime[i])
				bt(1 << i, 420 - mtime[i], i, 1);
		}

		//print answer
		printf("%d\n", best_depth);
	}

	return 0;
}
