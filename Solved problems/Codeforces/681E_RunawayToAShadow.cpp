/**
 * Algorithms used:
 *   Pitagoras, Cosine Theorem, Join of overlapping intervals
 */
#include <cstdio>
#include <cmath>
#include <vector>
#include <algorithm>
using namespace std;

#define FOR(i,a,b) for (int i = a; i <= b; ++i)

typedef long long int ll;
const double PI = 4 * atan(1);
enum Type { OPEN, CLOSE };

struct Angle {
  double val;
  Type type;
  Angle(double v, Type t) : val(v), type(t) {}
  bool operator<(const Angle& a) const {
    return val < a.val;
  }
};
bool inCircle(ll x, ll y, ll cx, ll cy, ll cr) {
  return (x - cx) * (x - cx) + (y - cy) * (y - cy) <= cr * cr;
}
bool circlesIntersect(ll x1, ll y1, ll r1, ll x2, ll y2, ll r2) {
  return log((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)) < 2 * log(r1 + r2);
}
int main() {
  ll x0, y0, v, T;
  ll r0;
  int n;
  scanf("%I64d %I64d %I64d %I64d", &x0, &y0, &v, &T);
  scanf("%d", &n);
  r0 = v * T;
  vector<Angle> angles;
  FOR(i,1,n)
  {
    ll cx, cy, cr;
    scanf("%I64d %I64d %I64d", &cx, &cy, &cr);
    if (inCircle(x0, y0, cx, cy, cr)) {
      puts("1.00000000000");
      return 0;
    } else if (circlesIntersect(x0, y0, r0, cx, cy, cr)) {
      double cDist = sqrt((x0 - cx) * (x0 - cx) + (y0 - cy) * (y0 - cy));
      double tDist = sqrt(cDist * cDist - cr * cr);
      double delta = (tDist <= r0) ?
        atan(cr / tDist) :
        acos((cDist * cDist + r0 * r0 - cr * cr) / (2 * cDist * r0));
      double angle = atan2(y0 - cy, x0 - cx);
      if (angle < 0) angle += 2 * PI;
      double begin = angle - delta;
      double end = angle + delta;
      if (begin < 0) {
        angles.push_back(Angle(2 * PI + begin, OPEN));
        angles.push_back(Angle(2 * PI, CLOSE));
        begin = 0;
      }
      if (end > 2 * PI) {
        angles.push_back(Angle(0, OPEN));
        angles.push_back(Angle(end - 2 * PI, CLOSE));
        end = 2 * PI;
      }
      angles.push_back(Angle(begin, OPEN));
      angles.push_back(Angle(end, CLOSE));
    }
  }
  if (angles.empty()) {
    puts("0.00000000000");
    return 0;
  }
  sort(angles.begin(), angles.end());
  double total = 0;
  double begin;
  int count = 0;
  for (Angle& angle : angles) {
    if (angle.type == OPEN) {
      if (count++ == 0)
      begin = angle.val;
    } else {
      if (--count == 0)
      total += angle.val - begin;
    }
  }
  double prob = min(total / (2 * PI), 1.0);
  printf("%1.11lf\n", prob);
  return 0;
}
