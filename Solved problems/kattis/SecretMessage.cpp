#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for (int i=a; i<=b; ++i)
#define invrep(i,a,b) for (int i=a; i>=b; --i)
#define MAXL 10000

int minsqrt(int x) {
  int i = 1, j = x;
  while (i < j) {
    int m = (i+j)/2;
    if (m*m >= x)
      j = m;
    else
      i = m + 1;
  }
  return i;
}

int N, L;
char board[MAXL][MAXL];

int main() {
  string line;
  scanf("%d\n", &N);
  while(N--) {
    getline(cin, line);
    L = line.size();
    int mroot = minsqrt(L);
    // printf("mroot = %d\n", mroot); 
    int p2 = mroot * mroot;
    int r = 0, c = 0, i = 0;
    while(i < p2) {
      if (i < L)
        board[r][c] = line[i];
      else
        board[r][c] = '*';
      ++i;
      if (++r == mroot) {
        r = 0; ++c; 
      }
    }
    rep(r,0,mroot-1) {
      invrep(c,mroot-1,0) {
        if (board[r][c] != '*')
          printf("%c",board[r][c]);
      }
    }
    puts("");
  }
  return 0;
}