// tags: implementation
#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

char board[100][101];
int m,n;

int dirs[4][2] = {
  {0, 1},
  {0, -1},
  {1, 0},
  {-1, 0}
};

void bfs(int r, int c) {
  board[r][c] = '#';
  queue<pii> q;
  q.push(pii(r,c));
  while (!q.empty()) {
    pii u = q.front(); q.pop();
    rep(i,0,3) {
      int rr = u.first + dirs[i][0];
      int cc = u.second + dirs[i][1];
      if (0 <= rr and rr < m && 0 <= cc and cc < n and board[rr][cc] == '-') {
        board[rr][cc] = '#';
        q.push(pii(rr,cc));
      }
    }
  }
}

int main() {

  int _case = 1;
  while(scanf("%d%d", &m, &n) == 2) {

    rep(r,0,m-1)
      scanf("%s\n", board[r]);

    int count = 0;

    rep(r,0,m-1) {
      rep(c,0,n-1) {
        if (board[r][c] == '-') {
          bfs(r,c);
          count++;
        }
      }
    }

    printf("Case %d: %d\n", _case, count);
    _case++;

  }

  return 0;
}