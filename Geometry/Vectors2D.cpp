/* ================ */
/* Angle Comparison */
/* ================ */

// --------------
// method 1: atan2()
#include <cmath>
const double PI = atan(1) * 4;
double angle(double x, double y) {
  double a = atan2(y, x);
  return (a < 0) ? (a + 2 * PI) : a;
}
int cmpAngles(double x1, double y1, double x2, double y2) {
  double a1 = angle(x1,y1);
  double a2 = angle(x2,y2);
  return (a1 < a2) ? -1 : (a1 == a2) ? 0 : 1;
}

// ----------------------------
// method 2: quadrants + slopes
// this is the prefered method when coordinates
// are given as integers
#include <cmath>
enum Quadrant { UpRight, Up, UpLeft, DownLeft, Down, DownRight };
int getQuadrant(int x, int y) {
  if (x > 0) return (y >= 0) ? UpRight : DownRight;
  if (x < 0) return (y >= 0) ? UpLeft : DownLeft;
  return (y >= 0) ? Up : Down;
}
int cmpAngles(int x1, int y1, int x2, int y2) {
  int q1 = getQuadrant(x1,y1);
  int q2 = getQuadrant(x2,y2);
  if (q1 > q2) return 1;
  if (q1 < q2) return -1;
  int m1 = abs(y1 * x2);
  int m2 = abs(y2 * x1);
  switch (q1) {
    case UpRight:
    case DownLeft:
      return (m1 > m2) ? 1 : (m1 < m2) ? -1 : 0;
    case UpLeft:
    case DownRight:
      return (m1 > m2) ? -1 : (m1 < m2) ? 1 : 0;
    default: return 0;
  }
}