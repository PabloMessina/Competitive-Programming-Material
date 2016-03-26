#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;

typedef vector<int> vi;

char buffer[100];
char layers[50][50][51];

struct V3 {
	int lay;
	int row;
	int col;
};

int shifts[3][6] = { { 1, -1, 0, 0, 0, 0 }, { 0, 0, 1, -1, 0, 0 }, { 0, 0, 0, 0,
		1, -1 } };

void randomInput(int t) {
	srand(time(NULL));
	char cs[] = "abcd*";
	int length = strlen(cs);
	int m, k, p;
	while (t-- > 0) {
		p = 2 + rand() % 49;
		k = 2 + rand() % 49;
		m = 2 + rand() % 9;
		printf("%d %d %d\n", p, k, m);
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < p; ++j) {
				for (int l = 0; l < k; ++l) {
					printf("%c", cs[rand() % length]);
				}
				printf("\n");
			}
			printf("\n");
		}
	}
}

int main() {
	//setvbuf(stdout, NULL, _IONBF, 0);	 //debugging
//	randomInput(50);
//	printf("===================\n");
	int _case = 1;
	int p, k, m;
	while (scanf("%d %d %d", &p, &k, &m) == 3) {

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < p; ++j) {
				scanf(" %[^\n]",layers[i][j]);
			}
		}
		vector<vi> counts(4, vi());
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < p; ++j) {
				for (int l = 0; l < k; ++l) {
					char c = layers[i][j][l];
					if (c == '*')
						continue;
					layers[i][j][l] = '*';
					int count = 0;
					queue<V3> q;
					q.push( { i, j, l });
					while (!q.empty()) {
						V3 u = q.front();
						q.pop();
						for (int x = 0; x < 6; ++x) {
							int lay = u.lay + shifts[0][x];
							int row = u.row + shifts[1][x];
							int col = u.col + shifts[2][x];
							if (lay >= 0 && lay < m && row >= 0 && row < p
									&& col >= 0 && col < k
									&& layers[lay][row][col] == c) {
								layers[lay][row][col] = '*';
								q.push( { lay, row, col });
							}
						}
						count++;
					}
					counts[c - 'a'].push_back(count);
				}
			}
		}

		if (_case > 1)
			printf("\n");
		printf("Case %d:\n", _case);

		for (char c = 'a'; c <= 'd'; ++c) {
			vi& v = counts[c - 'a'];
			if (v.size() == 0) {
				printf("%c 0\n", c);
			} else {
				sort(v.begin(), v.end());
				printf("%c", c);
				for (int i = v.size() - 1; i >= 0; --i) {
					printf(" %d", v[i]);
				}
				printf("\n");
			}
		}
		_case++;

		if (feof(stdin))
			break;
	}
//	printf("===================\n");
	return 0;
}
