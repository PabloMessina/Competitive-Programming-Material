#include <cstdio>
#include <algorithm>
using namespace std;
#define FOR(i,i0,n) for(int i = i0; i < n; ++i)

int M, N;
char C;

char background[1000][1000];
char frame1[1000][1001];
char frame2[1000][1001];
char answer[1000][1001];

struct Bbox {
  int minR;
  int minC;
  int maxR;
  int maxC;
};

void updateBbox(Bbox& bbox, int row, int col)  {
  bbox.minR = min(bbox.minR, row);
  bbox.minC = min(bbox.minC, col);
  bbox.maxR = max(bbox.maxR, row);
  bbox.maxC = max(bbox.maxC, col);
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);  //debugging
  while(scanf("%d %d '%c'", &M, &N, &C) && M) {
    // printf("M = %d, N = %d, C = %c\n",M,N,C);
    Bbox bbox1 = { M,N,-1,-1 };
    Bbox bbox2 = { M,N,-1,-1 };
    // read frame 1
    FOR(i,0,M) {
      scanf("%s", frame1[i]);
      FOR(j,0,N) {
        if (frame1[i][j] == C) {
          updateBbox(bbox1, i, j);
        } else {
          background[i][j] = frame1[i][j];
        }
      }
    }
    // read frame 2
    FOR(i,0,M) {
      scanf("%s", frame2[i]);
      FOR(j,0,N) {
        if (frame2[i][j] == C) {
          updateBbox(bbox2, i, j);
        } else {
          background[i][j] = frame2[i][j];
        }
      }
    }
    // generate answer
    int offsetR = bbox2.minR - bbox1.minR;
    int offsetC = bbox2.minC - bbox1.minC;
    FOR(i,0,M) {
      FOR(j,0,N) answer[i][j] = background[i][j];
      answer[i][N] = '\0';
    }

    // printf("offsetR = %d\n",offsetR);
    // printf("offsetC = %d\n",offsetC);

    int minR = max(0, bbox2.minR + offsetR);
    int maxR = min(M-1, bbox2.maxR + offsetR);
    int minC = max(0, bbox2.minC + offsetC);
    int maxC = min(N-1, bbox2.maxC + offsetC);

    // printf("minR = %d, maxR = %d, minC = %d, maxC = %d\n",minR,maxR,minC,maxC);

    FOR(r,minR,maxR+1) {
      FOR(c,minC,maxC+1) {
        if (frame2[r-offsetR][c-offsetC] == C) {
          answer[r][c] = C;
        }
      }
    }

    // puts("==============");
    FOR(r,0,M) printf("%s\n",answer[r]);
    puts("");

  }
  return 0;
}
