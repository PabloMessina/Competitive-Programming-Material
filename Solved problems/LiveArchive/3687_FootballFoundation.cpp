#include <cstdio>
#include <vector>
using namespace std;

#define FOR(i,n) for(int i = 0; i < n; ++i)
#define vecMatrix(name,type,w,h) vector<vector<type> > name(h, vector<type>(w));

int main() {
	int rows, cols, c0;
	while (true) {
		beginCaseLoop:
		scanf("%d %d %d", &rows, &cols, &c0);
		if (cols == 0) break;
		c0--;
		// create matrixes
		vecMatrix(charMap,char,cols,rows);
		vecMatrix(stepMap,int,cols,rows);
		// read lines
		char buff[cols + 1];
		FOR(r, rows) {
			scanf("%s", buff);
			FOR(c, cols) charMap[r][c] = buff[c];
		}
		// execute steps
		int steps = 0;
		int c = c0;
		int r = 0;
		while (true) {
			steps++;
			int prevSteps = stepMap[r][c];

			if (prevSteps > 0) {
				printf("%d step(s) before a loop of %d step(s)\n", prevSteps - 1, steps - prevSteps);
				goto beginCaseLoop;
			}
			stepMap[r][c] = steps;
			switch(charMap[r][c]) {
				case 'N':
					r--;
					if (r == -1) {
						printf("%d step(s) to exit\n", steps);
						goto beginCaseLoop;
					}
					break;
				case 'S':
					r++;
					if (r == rows) {
						printf("%d step(s) to exit\n", steps);
						goto beginCaseLoop;
					}
					break;
				case 'W':
					c--;
					if (c == -1) {
						printf("%d step(s) to exit\n", steps);
						goto beginCaseLoop;
					}
					break;
				default: // case 'E'
					c++;
					if (c == cols) {
						printf("%d step(s) to exit\n", steps);
						goto beginCaseLoop;
					}
					break;
			}
		}
	}
	return 0;
}