#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)

int H, L;
int board[200][200];

int shifts[4][2] = {
  {0, 1},
  {0, -1},
  {1, 0},
  {-1, 0}
};

int dfs(int r, int c, int color) {
  if (r < 0 || r >= H || c < 0 || c >= L)
    return 0;
  if (board[r][c] != color) 
    return 0;

  board[r][c] = -1;
  int tot = 1;
  rep(i,0,3) {
    int rr = r + shifts[i][0];
    int cc = c + shifts[i][1];
    tot += dfs(rr, cc, color);
  }
  return tot;
}

int main() {
  while (scanf("%d%d", &H, &L) == 2) {

    rep(r,0,H-1) rep(c,0,L-1) scanf("%d", &board[r][c]);

    int marea = 999999;
    rep(r,0,H-1) {
      rep(c,0,L-1) {
        if (board[r][c] != -1) {          
          marea = min(dfs(r,c,board[r][c]), marea);
        }
      }
    }

    printf("%d\n", marea);
  }
  return 0;
}