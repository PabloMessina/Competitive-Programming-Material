#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
#define FOR(i,a,b) for(int i = a; i <= b; ++i)

struct Circle {
  double offset;
  int radius;
  Circle (double o, int r) : offset(o), radius(r) {}
};

int main() {
  int N;
  double left, right;
  int r;
  while (scanf("%d", &N) == 1) {
    left = 0;
    right = 0;
    vector<Circle> circles;
    FOR(i,0,N-1)
    {
      scanf("%d", &r);
      double offset = 0;
      FOR(j,0,i-1) {
        Circle c = circles[j];
        double d = sqrt((c.radius + r) * (c.radius + r) - (c.radius - r) * (c.radius - r));
        offset = max(offset, c.offset + d);
      }
      left = min(left, offset - r);
      right = max(right, offset + r);
      circles.push_back(Circle(offset, r));
    }
    double width = right - left;
    printf("%.8lf\n", width);
  }
  return 0;
}
