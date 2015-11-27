#include <cstdio>
#include <vector>
#define INVALID -9999
using namespace std;

typedef vector<int> vi;

#define MAXN 100005

vi A(MAXN);
vi st(4 * MAXN);
int n;
int k;

int left(int p) {
	return p << 1;
}
int right(int p) {
	return (p << 1) + 1;
}

void build(int p, int L, int R) {
	if (L == R)
		st[p] = A[L];
	else {
		build(left(p), L, (L + R) / 2);
		build(right(p), (L + R) / 2 + 1, R);
		st[p] = st[left(p)] * st[right(p)];
	}
}

int rangeQuery(int p, int L, int R, int i, int j) {
	if (i > R || j < L)
		return INVALID;
	if (i <= L && R <= j)
		return st[p];
	int r1 = rangeQuery(left(p), L, (L + R) / 2, i, j);
	int r2 = rangeQuery(right(p), (L + R) / 2 + 1, R, i, j);
	if (r1 == INVALID)
		return r2;
	if (r2 == INVALID)
		return r1;
	return r1 * r2;
}

int update_point(int p, int L, int R, int idx, int new_value) {
	if (L == R)
		return st[p] = A[L] = new_value;

	int m = (L + R) / 2;
	if (idx <= m) {
		int r1 = update_point(left(p), L, m, idx, new_value);
		int r2 = st[right(p)];
		return st[p] = r1 * r2;
	} else {
		int r1 = st[left(p)];
		int r2 = update_point(right(p), m + 1, R, idx, new_value);
		return st[p] = r1 * r2;
	}
}

int rangeQuery(int i, int j) {
	return rangeQuery(1, 0, n - 1, i, j);
}

int update_point(int idx, int new_value) {
	return update_point(1, 0, n - 1, idx, new_value);
}

char buff[10];

int main() {

//	setvbuf(stdout, NULL, _IONBF, 0);

	while (scanf("%d %d", &n, &k) == 2) {

//		printf("n = %d, k = %d\n",n,k);

		for (int i = 0; i < n; ++i) {
			int x;
			scanf("%d", &x);
			A[i] = (x < 0) ? -1 : (x > 0) ? 1 : 0;
//			printf("x_%d = %d, -> %d\n",i,x,A[i]);
		}

		build(1, 0, n - 1);

		for (int i = 0; i < k; ++i) {
			char c;
			int x, y;
			scanf("%s %d %d", buff, &x, &y);
			c = buff[0];

//			printf("c = %c, %d, %d\n", c, x, y);
			if (c == 'C') {
				x--;
				y = (y < 0) ? -1 : (y > 0) ? 1 : 0;
				update_point(x, y);
			} else {
				x--;
				y--;
				int r = rangeQuery(x, y);
				if (r == -1)
					printf("-");
				else if (r == 1)
					printf("+");
				else
					printf("0");
			}
		}
		printf("\n");
	}

	return 0;
}
