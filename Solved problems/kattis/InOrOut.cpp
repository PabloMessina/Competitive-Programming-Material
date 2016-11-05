#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int main() {
  double x, y; int r;
  int _case = 1;

  while (scanf("%lf%lf%d",&x,&y,&r) == 3) {

    bool in = true;
    double cx = 0, cy = 0;
    double xx, yy;

    rep(i, 0, r) {

      if (cx*cx + cy*cy > 4.0) {
        in = false;
        break;
      }

      xx = cx; yy = cy;
      cx = xx*xx - yy*yy + x;
      cy = 2*xx*yy + y;
    }

    if (in) printf("Case %d: IN\n", _case);
    else printf("Case %d: OUT\n", _case);
    _case++;
  }

  return 0;
}