#include <cstdio>
#include <cstring>
using namespace std;

int board[100][100];
int board_aux[100][100];

int nextNumber(int x, int n) {
	return (x + 1) % n;
}
void updateBoard(int r, int c, int n) {
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j) {
			int num = board[i][j];
			int next = nextNumber(num, n);

			int up = i - 1;
			int down = i + 1;
			int left = j - 1;
			int right = j + 1;

			if (up >= 0 && board[up][j] == next) {
				board_aux[up][j] = num;
			}
			if (down < r && board[down][j] == next) {
				board_aux[down][j] = num;
			}
			if (left >= 0 && board[i][left] == next) {
				board_aux[i][left] = num;
			}
			if (right < c && board[i][right] == next) {
				board_aux[i][right] = num;
			}
		}
	}
	memcpy(board,board_aux,sizeof(board_aux));
}

int main() {

	while (true) {
		int n, r, c, k;
		scanf("%d %d %d %d", &n, &r, &c, &k);
		if (n == 0 && r == 0 && c == 0 && k == 0)
			break;

		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				scanf("%d", &board[i][j]);
			}
		}

		memcpy(board_aux, board, sizeof(board));

		for (int i = 0; i < k; ++i) {
			updateBoard(r, c, n);
		}

		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) {
				if (j)
					printf(" %d", board[i][j]);
				else
					printf("%d", board[i][j]);
			}
			printf("\n");
		}

	}

	return 0;
}
