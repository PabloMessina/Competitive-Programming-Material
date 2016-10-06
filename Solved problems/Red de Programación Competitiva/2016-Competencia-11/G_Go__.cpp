#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define WHITE 1
#define BLACK 2

int N, P;

int board[500][500];

int wcount[500][500];
int bcount[500][500];

void dp() {
  rep(r,0,N-1) {
    rep(c,0,N-1) {
      int brc = board[r][c];

      if (brc == WHITE) {
        wcount[r][c] = 1;
        bcount[r][c] = 0;
      } else if (brc == BLACK) {
        bcount[r][c] = 1;
        wcount[r][c] = 0;
      } else {
        bcount[r][c] = 0;
        wcount[r][c] = 0;
      }

      if (r > 0) {
        wcount[r][c] += wcount[r-1][c];
        bcount[r][c] += bcount[r-1][c];
      }
      if (c > 0) {
        wcount[r][c] += wcount[r][c-1];
        bcount[r][c] += bcount[r][c-1];        
      }
      if (r > 0 && c > 0) {
        wcount[r][c] -= wcount[r-1][c-1];
        bcount[r][c] -= bcount[r-1][c-1];        
      }

    }
  }
}

int query_white(int r, int c, int size) {
  int r1 = r + size-1;
  int c1 = c + size-1;
  int ans = wcount[r1][c1];
  if (c > 0)
    ans -= wcount[r1][c-1];
  if (r > 0)
    ans -= wcount[r-1][c1];
  if (r > 0 && c > 0)
    ans += wcount[r-1][c-1];
  return ans;
}

int query_black(int r, int c, int size) {
  int r1 = r + size-1;
  int c1 = c + size-1;
  int ans = bcount[r1][c1];
  if (c > 0)
    ans -= bcount[r1][c-1];
  if (r > 0)
    ans -= bcount[r-1][c1];
  if (r > 0 && c > 0)
    ans += bcount[r-1][c-1];
  return ans;
}

int get_scores(int& bscore, int& wscore) {

  bscore = 0;
  wscore = 0;
  rep(size,1,N) {
    int maxr = N - size;
    int maxc = N - size;
    rep(r,0,maxr) {
      rep(c,0,maxc) {

        int bc = query_black(r,c,size);
        int wc = query_white(r,c,size);

        if (bc == 0 && wc > 0) wscore++;
        if (bc > 0 && wc == 0) bscore++;
      }
    }
  }
}

int main() {

  while (scanf("%d%d", &N, &P) == 2) {

    memset(board, 0, sizeof board);

    rep(i,1,P) {
      int r, c; scanf("%d%d",&r,&c);
      r--, c--;
      board[r][c] = BLACK;
    }

    rep(i,1,P) {
      int r, c; scanf("%d%d",&r,&c);
      r--, c--;
      board[r][c] = WHITE;
    }

    dp();

    int bs, ws;
    get_scores(bs, ws);

    printf("%d %d\n", bs, ws);

  }

  return 0;
}