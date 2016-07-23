//============================================================================
// Name        : cpp.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;

#define FOR(i,i0,n) for(int i = i0; i < n; ++i)
int R,C;
int steps[100][100][16];
char map[101][101];
enum color { blue=1, yellow=2, red=4, green=8 };

struct triple {
  int row; int col; int keys;
  triple(int c, int r, int k) : row(c), col(r), keys(k) {}
};

int shifts[4][2] = {
  { 0, 1 },
  { 0, -1 },
  { 1, 0 },
  { -1, 0 }
};

int main() {
  begin:
  while(scanf("%d %d", &R, &C) && R && C) {
    memset(steps, -1, sizeof steps);
    queue<triple> q;
    int str, stc;
    FOR(i,0,R) {
      scanf("%s", map[i]);
      FOR(j,0,C) {
        char c = map[i][j];
        if (c == '*') {
          str = i;
          stc = j;
        }
      }
    }
    q.push(triple(str, stc, 0));
    steps[str][stc][0] = 0;
    while (!q.empty()) {
      triple t = q.front(); q.pop();
//      printf("t.r, t.c, t.k = %d, %d, %d\n", t.row, t.col, t.keys);
      FOR(i,0,4) {
        int r = shifts[i][0] + t.row;
        int c = shifts[i][1] + t.col;
        char mrc = map[r][c];
        if (r < 0 || r >= R || c < 0 || c >= C || mrc == '#') continue;
        if (mrc == 'B'  && (t.keys & blue) == 0) continue;
        if (mrc == 'Y'  && (t.keys & yellow) == 0) continue;
        if (mrc == 'R'  && (t.keys & red) == 0) continue;
        if (mrc == 'G'  && (t.keys & green) == 0) continue;
        if (mrc == 'X') {
          printf("Escape possible in %d steps.\n", steps[t.row][t.col][t.keys] + 1);
          goto begin;
        }
        int k2;
        if (mrc == 'b' && steps[r][c][k2 = (t.keys | blue)] == -1) {
          q.push(triple(r,c,k2));
          steps[r][c][k2] = steps[t.row][t.col][t.keys] + 1;
          continue;
        }
        if (mrc == 'r' && steps[r][c][k2 = (t.keys | red)] == -1) {
          q.push(triple(r,c,k2));
          steps[r][c][k2] = steps[t.row][t.col][t.keys] + 1;
          continue;
        }
        if (mrc == 'g' && steps[r][c][k2 = (t.keys | green)] == -1) {
          q.push(triple(r,c,k2));
          steps[r][c][k2] = steps[t.row][t.col][t.keys] + 1;
          continue;
        }
        if (mrc == 'y' && steps[r][c][k2 = (t.keys | yellow)] == -1) {
          q.push(triple(r,c,k2));
          steps[r][c][k2] = steps[t.row][t.col][t.keys] + 1;
          continue;
        }
        // default: .
        if (steps[r][c][k2 = t.keys] == -1) {
          q.push(triple(r,c,k2));
          steps[r][c][k2] = steps[t.row][t.col][t.keys] + 1;
          continue;
        }
      }
    }
    puts("The poor student is trapped!");
  }
  return 0;
}
