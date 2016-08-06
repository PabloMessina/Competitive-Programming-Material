#include <cstdio>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

double x[2][3];
double y[2][3];
int scores[2];

void computeScore(int p) {
  scores[p] = 0;
  rep(i,0,2) {
    double d = x[p][i] * x[p][i] + y[p][i] * y[p][i];
    // printf("scores[%d] = %d, d = %lf\n", p, scores[p], d);
    if (d <= 9.0) scores[p] += 100;
    else if (d <= 36.0) scores[p] += 80;
    else if (d <= 81.0) scores[p] += 60;
    else if (d <= 144.0) scores[p] += 40;
    else if (d <= 225.0) scores[p] += 20;
  }
}

int main () {
  while (true) {
    rep(i,0,2) scanf("%lf%lf",&x[0][i], &y[0][i]);
    rep(i,0,2) scanf("%lf%lf",&x[1][i], &y[1][i]);
    if (x[0][0] == -100) break;
    computeScore(0);
    computeScore(1);
    if (scores[0] == scores[1]) {
      printf("SCORE: %d to %d, TIE.\n", scores[0], scores[1]);
    } else {
      printf("SCORE: %d to %d, PLAYER %d WINS.\n",
        scores[0], scores[1], (scores[0] > scores[1] ? 1 : 2));
    }
  }
  return 0;
}