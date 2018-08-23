#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

struct time {
	int h;
	int m;
	int s;
	char tag;

	bool operator<(const time& x) const {
		if (h < x.h)
			return true;
		else if (h == x.h) {
			if (m < x.m)
				return true;
			else if (m == x.m && s < x.s)
				return true;
		}
		return false;
	}

};

time times[64801];

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	int n;
	while (true) {
		scanf("%d", &n);
		if (n == 0)
			break;

		int entries = 0;

		for (int i = 0; i < n; ++i) {
			time t;
			scanf("%d:%d:%d	%c", &t.h, &t.m, &t.s, &t.tag);
			if(t.tag == 'E')
				entries++;
			times[i] = t;
		}

		sort(times, times + n);

		int inside = 0;
		int max_inside = -1;
		int halfn = n / 2;

		for (int i = 0; i < n; ++i) {
			if (times[i].tag == 'E') {
				inside++;
				if (max_inside < inside)
					max_inside = inside;
			} else if (times[i].tag == 'X') {
				inside--;
			} else if (entries < halfn) {
				entries++;
				inside++;
				if (max_inside < inside)
					max_inside = inside;
				times[i].tag = 'E';
			} else {
				inside--;
				times[i].tag = 'X';
			}
		}


		printf("%d\n", max_inside);

	}

	return 0;
}
