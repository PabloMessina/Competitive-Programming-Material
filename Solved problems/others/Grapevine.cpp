#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cstring>
using namespace std;

struct Cell {
	int i;
	int j;
	int height;
	bool operator<(const Cell& x) const {
		return height < x.height;
	}
	bool operator==(const Cell& x) const {
		return height == x.height;
	}
};

int H[500][500];
Cell cells[250000];

int lowerBoundDiagonal(int upindex, int height) {
	int i2 = cells[upindex].i;
	int j2 = cells[upindex].j;
	int min_i = min(i2, j2);
	int i1 = i2 - min_i;
	int j1 = j2 - min_i;

	int l = 0, r = min_i;
	while (l < r) {
		int m = (l + r) / 2;
		if (H[i1 + m][j1 + m] < height) {
			l = m + 1;
		} else {
			r = m;
		}
//		printf("lowerbound\n");
	}
	if (H[i1 + l][j1 + l] >= height)
		return i2 - i1 - l + 1;
	return -1;
}

int upperBound(int height, int size) {
	int l = 0, r = size - 1;
	while (l < r) {
		int m = (l + r + 1) / 2;
		if (cells[m].height > height) {
			r = m - 1;
		} else {
			l = m;
		}
//		printf("\tl = %d, r = %d, m = %d, cells[%d].height = %d\n", l, r, m, m,
//				cells[m].height);
	}
	if (cells[l].height <= height)
		return l;
	return -1;
}

int main() {

	setvbuf(stdout, NULL, _IONBF, 0);

	while (true) {

		int n, m;
		scanf("%d %d", &n, &m);
		if (n == 0 && m == 0)
			break;

		int nm = n * m;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				int height;
				Cell cell;
				scanf("%d", &height);
				H[i][j] = height;
				cell.i = i;
				cell.j = j;
				cell.height = height;
				cells[i * m + j] = cell;
			}
		}

		sort(cells, cells + nm);

//		for (int i = 0; i < nm; ++i) {
//			printf("cells[%d].height = %d\n", i, cells[i].height);
//		}

		int q;
		scanf("%d", &q);
		for (int i = 0; i < q; ++i) {
			int l, u;
			scanf("%d %d", &l, &u);
			int maxsize = 0;
			int upindex = upperBound(u, nm);

//			printf("u = %d, l = %d, upindex = %d\n", u, l, upindex);

			if (upindex != -1) {
				for (; upindex >= 0; upindex--) {

					int size = lowerBoundDiagonal(upindex, l);
					if (size > maxsize)
						maxsize = size;
				}
			}

			printf("%d\n", maxsize);
		}
		printf("-\n");
	}

	return 0;
}