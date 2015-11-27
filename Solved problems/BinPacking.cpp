#include <cstdio>
#include <algorithm>
using namespace std;

int main() {

	int lengths[100000];

	int cases;
	scanf("%d", &cases);

	bool first_time = true;
	while (cases--) {
		int n, l;
		scanf("%d %d", &n, &l);
		for (int i = 0; i < n; ++i)
			scanf("%d", &lengths[i]);
		sort(lengths, lengths + n);
		int count = 0;
		int first = 0, last = n - 1;

		while (true) {
			if (first == last) {
				count++;
				break;
			} else if (first > last) {
				break;
			}
			if (lengths[last] + lengths[first] <= l) {
				last--;
				first++;
			} else
				last--;
			count++;
		}
		if (first_time)
			first_time = false;
		else
			printf("\n");
		printf("%d\n", count);
	}

	return 0;
}