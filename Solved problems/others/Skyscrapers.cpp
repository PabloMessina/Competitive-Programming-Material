// tags: implementation
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAXN 1000000
typedef vector<int> vi;

vi heights(MAXN);
vi indexes(MAXN);
vector<bool> under_water(MAXN);

bool cmp(int i, int j) {
	return heights[i] < heights[j];
}

int main() {
	int t;
	scanf("%d", &t);
	while (t-- > 0) {
		int n, d;
		scanf("%d %d", &n, &d);
		for (int i = 0; i < n; ++i) {
			scanf("%d", &heights[i]);
			indexes[i] = i;
		}
		sort(indexes.begin(), indexes.begin() + n, cmp);
		vi answers;
		under_water.assign(n, false);
		int curr_i = 0;
		int groups = 1;
		for (int i = 0; i < d; ++i) {
			int wh;
			scanf("%d", &wh);
			int index;
			while (curr_i < n && heights[(index = indexes[curr_i])] <= wh) {
				under_water[index] = true;
				bool uw1 = (index > 0) ? under_water[index - 1] : true;
				bool uw2 = (index < n - 1) ? under_water[index + 1] : true;
				if (uw1 && uw2)
					groups--;
				else if (!uw1 && !uw2)
					groups++;
				curr_i++;
			}
			answers.push_back(groups);
		}
		for (int i = 0; i < d; ++i) {
			if (i > 0)
				printf(" %d", answers[i]);
			else
				printf("%d", answers[i]);
		}
		printf("\n");
	}
	return 0;
}
