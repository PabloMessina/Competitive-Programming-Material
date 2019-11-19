// tags: graphs, BFS, binary search
#include <cstdio>
#include <vector>
#include <cstring>
#include <utility>
#include <tuple>
#include <queue>
using namespace std;

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
typedef pair<int, int> ii;

int N, S;
char board[800][801];
int reach[800][800];
int steps[800][800];
int shifts[4][2] = { { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 } };
int Tm;

bool isSafe(ii start) {
  if (reach[start.first][start.second] <= Tm) return false;
  memset(steps, -1, sizeof steps);
  queue<ii> q;
  q.push(start);

  steps[start.first][start.second] = 0;
  while (!q.empty()) {
    ii cell = q.front();
    q.pop();
    int stp = steps[cell.first][cell.second];
    int ntime = (stp + 1) / S;
    FOR (i, 0, 3)
    {
      int r = cell.first + shifts[i][0];
      int c = cell.second + shifts[i][1];
      if (r < 0 || r >= N || c < 0 || c >= N)
        continue;
      if (steps[r][c] >= 0)
        continue;
      char brc = board[r][c];
      if (brc == 'D')
        return true;
      if (brc == 'T')
        continue;
      if (reach[r][c] <= ntime + Tm)
        continue;
      q.push(ii(r, c));
      steps[r][c] = stp + 1;
    }
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    scanf("%d %d", &N, &S);
    ii mcell;
    vector<ii> hcells;
    // read board
    FOR(i, 0, N-1)
    {
      scanf("%s", board[i]);
      FOR(j,0,N-1)
      {
        char c = board[i][j];
        if (c == 'M') {
          mcell = ii(i, j);
        } else if (c == 'H') {
          hcells.push_back(ii(i, j));
        }
      }
    }
    // set reach distances for bees
    memset(reach, -1, sizeof reach);
    queue<ii> q;
    for (ii& cell : hcells) {
      q.push(cell);
      reach[cell.first][cell.second] = 0;
    }
    while (!q.empty()) {
      ii cell = q.front();
      q.pop();
      FOR(i,0,3)
      {
        int r = cell.first + shifts[i][0];
        int c = cell.second + shifts[i][1];
        if (r < 0 || r >= N || c < 0 || c >= N)
          continue;
        char brc = board[r][c];
        if (brc == 'T' || brc == 'D' || reach[r][c] >= 0)
          continue;

        reach[r][c] = reach[cell.first][cell.second] + 1;
        q.push(ii(r, c));
      }
    }

    // do binary search
    int tmin = 0;
    int tmax = N * N;
    while (tmin < tmax) {
      Tm = (tmin + tmax) / 2;
      if (!isSafe(mcell)) {
        tmax = Tm;
      }
      else {
        tmin = Tm + 1;      }
    }
    printf("%d\n", tmax - 1);
  }
  return 0;
}
