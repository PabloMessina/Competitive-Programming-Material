/**
 * Algorithm used:
 *	BFS (shortest path with edge's length = 1)
 */
#include <cstdio>
#include <queue>
#include <cstring>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)

struct Point {
	int row;
	int col;
	bool operator== (const Point &p) {
  	return (row == p.row && col == p.col);
  }
};
int matrix[100][100];
int dist[100][100];
int shifts[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

int main() {
	int t,n,m;
	Point a, b;
	scanf("%d",  &t);

	MAIN_LOOP:
	while(t-- > 0) {
		scanf("%d %d", &n, &m);
		FOR(i,m) FOR(j,n) scanf("%d", &matrix[i][j]);
		scanf("%d %d", &a.col, &a.row);
		scanf("%d %d", &b.col, &b.row);

		if (a == b) {
			puts("1");
		} else {

			memset(dist, 0, sizeof dist);
			queue<Point> q;
			q.push(a);
			dist[a.row][a.col] = 1; // path length from a to a is 1
			matrix[a.row][a.col] = 1; // so it's not visited again

			while(!q.empty()) {
				Point p = q.front(); q.pop();
				int d = dist[p.row][p.col];
				
				FOR(i,4) {
					int r = p.row + shifts[i][0];
					int c = p.col + shifts[i][1];
					// reachable + not visited
					if ((0 <= r && r < m && 0 <= c && c < n) && matrix[r][c] == 0) {
						Point p2 = {r,c};
						if (p2 == b) {
							printf("%d\n", d + 1);
							goto MAIN_LOOP;
						}
						matrix[r][c] = 1; // so it's not visited again
						dist[r][c] = d + 1; // remember path's length from a
						q.push(p2);
					}
				}
			}

		}
	}
	return 0;
}