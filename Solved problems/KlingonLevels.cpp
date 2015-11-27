#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		int n;
		scanf("%d", &n);
		if (n == 0)
			break;

		vector<vector<int> > scores(n);
		for (int i = 0; i < n; ++i) {
			int k;
			scanf("%d", &k);
			for (int j = 0; j < k; ++j) {
				int score;
				scanf("%d", &score);
				scores[i].push_back(score);
			}
			sort(scores[i].begin(), scores[i].end());
		}
		int minAccDiff = 9999999;

		for (int T = 0; T <= 1000; ++T) {
			int accDiff = 0;
			for (int i = 0; i < n; ++i) {
				vector<int>::iterator low = lower_bound(scores[i].begin(),
						scores[i].end(), T);
				int above = (scores[i].end() - low);
				int below = (low - scores[i].begin());
				accDiff += abs(above - below);
			}
			if (minAccDiff > accDiff)
				minAccDiff = accDiff;
		}

		printf("%d\n", minAccDiff);

	}

	return 0;
}
