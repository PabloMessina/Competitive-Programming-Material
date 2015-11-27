#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <queue>
#include <utility>
using namespace std;

#define MAXN 305

char buffer[4 * MAXN];
int _true = 1;

struct cell {
	cell() :
			up(0), down(0), left(0), right(0), visited(0) {
	}
	int up;
	int down;
	int left;
	int right;
	int visited;
};

vector<vector<cell> > cells(MAXN * 2, vector<cell>(MAXN * 2 + 1, cell()));

int N, R, C;
int count;

void bfs(int i, int j) {

	queue<pair<int, int> > nodes;

	nodes.push(make_pair(i, j));

	while (!nodes.empty()) {
		pair<int, int> node = nodes.front();
		nodes.pop();

		i = node.first;
		j = node.second;

		cell &c = cells[i][j];

		c.visited = _true;

		if (c.left != _true && cells[i][j - 1].visited != _true)
			nodes.push(make_pair(i, j - 1));
		if (c.right != _true && cells[i][j + 1].visited != _true)
			nodes.push(make_pair(i, j + 1));
		if (c.up != _true && cells[i - 1][j].visited != _true)
			nodes.push(make_pair(i - 1, j));
		if (c.down != _true && cells[i + 1][j].visited != _true)
			nodes.push(make_pair(i + 1, j));
	}
}

int main() {

//	setvbuf(stdout, NULL, _IONBF, 0);

	while (scanf("%d", &N) == 1) {

		R = 2 * N;
		C = 2 * N + 1;

		for (int i = 1; i < R; ++i) {
			scanf("%s", buffer);
			for (int j = 1; j <= N; ++j) {

				int mj = (i % 2 == 0) ? 2 * j : 2 * j - 1;

				if (buffer[j - 1] == 'H') {
					cells[i][mj].up = _true;
					cells[i][mj - 1].up = _true;
					cells[i - 1][mj].down = _true;
					cells[i - 1][mj - 1].down = _true;
				} else {
					cells[i][mj].left = _true;
					cells[i][mj - 1].right = _true;
					cells[i - 1][mj].left = _true;
					cells[i - 1][mj - 1].right = _true;
				}
			}
		}
		for (int i = 0; i < R; ++i) {
			cells[i][0].left = _true;
			cells[i][C - 1].right = _true;
		}
		for (int j = 0; j < C; ++j) {
			cells[0][j].up = _true;
			cells[R - 1][j].down = _true;
		}

		count = -1;
		for (int i = 0; i < R; ++i) {
			for (int j = 0; j < C; ++j) {
				if (cells[i][j].visited == _true)
					continue;
				count++;
				bfs(i, j);
			}
		}

		printf("%d\n", count);
		_true++;

	}
	return 0;
}