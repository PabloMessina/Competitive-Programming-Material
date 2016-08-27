#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXW 20
#define MAXL 20

enum DIR { RIGHT, LEFT, UP, DOWN };
int shifts[4][2] = {
  { 0 , 1 },
  { 0 , -1 },
  { -1 , 0 },
  { 1 , 0 }
};
int nextDir1[4] = {
  UP, DOWN, RIGHT, LEFT
};
int nextDir2[4] = {
  DOWN, UP, LEFT, RIGHT
};

int W,L;
char board[MAXL][MAXW+1];
int sr, sc;
int dir;


int main() {
  int house = 1;
  while(true) {
    scanf("%d%d",&W,&L);
    if (W == 0 && L == 0)
      break;

    rep(r,0,L-1) {
      scanf("%s", board[r]);
      rep(c,0,W-1) {
        if (board[r][c] == '*') {
          sr = r, sc = c;
          if (r == 0)
            dir = DOWN;
          else if (r == L-1)
            dir = UP;
          else if (c == 0)
            dir = RIGHT;
          else
            dir = LEFT;
        }
      }
    }

    int r = sr, c = sc;
    while(true) {
      r += shifts[dir][0];
      c += shifts[dir][1];
      if (board[r][c] == 'x') {
        board[r][c] = '&';
        break;
      }
      if (board[r][c] == '/') {
        dir = nextDir1[dir];
      } else if (board[r][c] == '\\') {
        dir = nextDir2[dir];
      }
    }

    printf("HOUSE %d\n", house++);
    rep(r, 0, L-1) {
      printf("%s\n", board[r]);
    }
  }

  return 0;
}
