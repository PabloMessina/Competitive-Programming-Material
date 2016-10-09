#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 4005

struct Point { double x, y; };
enum Where { LEFT, RIGHT };

int N, E, S;
Point pts[MAXN];
Point lbranch[MAXN];
Point rbranch[MAXN];
int lsize;
int rsize;

bool cached[MAXN + 1][MAXN + 1][2];
double memo[MAXN + 1][MAXN + 1][2];
double INF = 10000.0 * 2.0 * 4.0;

double dist(Point& a, Point& b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

double solve(int lc, int rc, int where) {
  // static int call = 0;
  // int mycall = call++;
  // printf("==> call=%d, solve(lc=%d, rc=%d, where=%d)\n",mycall, lc,rc,where);
  if (cached[lc][rc][where])
    return memo[lc][rc][where];

  Point prev_p = (where == LEFT ? lbranch[lc-1] : rbranch[rc-1]);

  // printf("\tprev_p = (%lf, %lf)\n",prev_p.x, prev_p.y);
  double ans;

  if (lc < lsize && rc < rsize) {
    ans = min(
      dist(prev_p, lbranch[lc]) + solve(lc+1, rc, LEFT),
      dist(prev_p, rbranch[rc]) + solve(lc, rc+1, RIGHT)
    );
  } else if (lc < lsize) {
    ans = dist(prev_p, lbranch[lc]) + solve(lc+1, rc, LEFT);
  } else if (rc < rsize) {
    ans = dist(prev_p, rbranch[rc]) + solve(lc, rc+1, RIGHT);
  } else {
    ans = dist(prev_p, pts[S]);
  }

  // printf("--> call=%d, ans = %lf\n", mycall, ans);
  cached[lc][rc][where] = true;
  return memo[lc][rc][where] = ans;
}

int main() {
  // read input
  scanf("%d%d%d",&N,&E,&S); E--, S--;
  rep(i, 0, N-1) scanf("%lf%lf", &pts[i].x, &pts[i].y);

  // collect left branch
  lsize = 0;
  for (int i = (E-1+N) % N; i != S; i = (i - 1 + N) % N) {
    lbranch[lsize++] = pts[i];
    // printf("lbranch[%d] = (%.0lf,%.0lf)\n",lsize-1,pts[i].x, pts[i].y);
  }

  // collect right branch
  rsize = 0;
  for (int i = E+1; i != S; i = (i + 1) % N) {
    rbranch[rsize++] = pts[i];
    // printf("rbranch[%d] = (%.0lf,%.0lf)\n",rsize-1,pts[i].x, pts[i].y);
  }

  // solve
  memset(cached, false, sizeof cached);
  double ans = INF;
  if (lsize > 0)
    ans = min(ans, dist(pts[E], lbranch[0]) + solve(1, 0, LEFT));
  if (rsize > 0)
    ans = min(ans, dist(pts[E], rbranch[0]) + solve(0, 1, RIGHT));
  printf("%.6lf", ans);
  return 0;
}