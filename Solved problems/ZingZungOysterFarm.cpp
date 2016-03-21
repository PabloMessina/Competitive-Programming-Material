#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
using namespace std;

struct Strip {
	int x1;
	int y1;
	int x2;
	int y2;
	int h;
};

struct Point {
	int x;
	int y;
};

Strip strips[2000];
int N, W;

int Board[1002][1002][5]; // [has_water?, lh,uh,rh,dh]

#define LEFT 1
#define UP 2
#define RIGHT 3
#define DOWN 4

int main() {

	while (true) {
		scanf("%d", &N);
		if (N == 0)
			break;
		for (int i = 0; i < N; ++i) {
			int x1, y1, x2, y2, h, aux;
			scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &h);
			if (x2 < x1) {
				aux = x1;
				x1 = x2;
				x2 = aux;
			} else if (y2 < y1) {
				aux = y1;
				y1 = y2;
				y2 = aux;
			}
			strips[i] = {501+x1,501+y1,501+x2,501+y2,h};
		}
		scanf("%d", &W);
		//remove strips shorter than water
		//and get bounding box
		//and write walls
		int count = 0;
		int minX = 9999, minY = 9999, maxX = -1, maxY = -1;
		memset(Board, 0, sizeof Board); //reset board
		for (int i = 0; i < N; ++i) {
			Strip& s = strips[i];
			if (s.h >= W) {
				strips[count++] = s;
				minX = min(minX, min(s.x1, s.x2));
				minY = min(minY, min(s.y1, s.y2));
				maxX = max(maxX, max(s.x1, s.x2));
				maxY = max(maxY, max(s.y1, s.y2));
				if (s.x1 == s.x2) { //vertical
					for (int y = s.y1; y < s.y2; ++y) {
						Board[s.x1][y][LEFT] = s.h;
						Board[s.x1 - 1][y][RIGHT] = s.h;
					}
				} else { // horizontal
					for (int x = s.x1; x < s.x2; ++x) {
						Board[x][s.y1][DOWN] = s.h;
						Board[x][s.y1 - 1][UP] = s.h;
					}
				}
			}
		}
		if (count == 0) {
			puts("0");
			continue;
		}
		minX--;
		minY--;
		maxX++;
		maxY++;
		//simulate with BFS
		int flood_count = 1;
		queue<Point> q;
		q.push( { minX, minY });
		Board[minX][minY][0] = 1;
		while (!q.empty()) {
			Point p = q.front();
			q.pop();
			if (p.x > minX && !Board[p.x - 1][p.y][0]
					&& Board[p.x][p.y][LEFT] < W) {
				q.push( { p.x - 1, p.y }); //left
				Board[p.x - 1][p.y][0] = 1;
				flood_count++;
			}
			if (p.x + 1 < maxX && !Board[p.x + 1][p.y][0]
					&& Board[p.x][p.y][RIGHT] < W) {
				q.push( { p.x + 1, p.y }); //right
				Board[p.x + 1][p.y][0] = 1;
				flood_count++;
			}
			if (p.y > minY && !Board[p.x][p.y - 1][0]
					&& Board[p.x][p.y][DOWN] < W) {
				q.push( { p.x, p.y - 1 }); //down
				Board[p.x][p.y - 1][0] = 1;
				flood_count++;
			}
			if (p.y + 1 < maxY && !Board[p.x][p.y + 1][0]
					&& Board[p.x][p.y][UP] < W) {
				q.push( { p.x, p.y + 1 }); //up
				Board[p.x][p.y + 1][0] = 1;
				flood_count++;
			}
		}
		int clean_area = (maxX - minX) * (maxY - minY) - flood_count;
		printf("%d\n", clean_area);
	}

	return 0;
}
