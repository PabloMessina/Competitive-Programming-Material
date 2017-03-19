/* =========================== */
/* Example of Point Definition */
/* =========================== */

struct Point {
  double x, y;
  bool operator==(const Point& p) const { return x==p.x && y == p.y; }
  Point operator+(const Point& p) const { return {x+p.x, y+p.y}; }
  Point operator-(const Point& p) const { return {x-p.x, y-p.y}; }
  Point operator*(double d) const { return {x*d, y*d}; }
  double norm2() const { return x*x + y*y; }
  double norm() const { return sqrt(norm2()); }
  double dot(const Point& p) const { return x*p.x + y*p.y; }
  Point unit() const {
    double d = norm();
    return {x/d,y/d};
  }
};

/* ================ */
/* Angle Comparison */
/* ================ */

// --------------
// method 1: atan2()
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

/* ====================================== */
/* Straight Line Hashing (integer coords) */
/* ===================================== */

struct Point {int x, y; };
struct Line { int a, b, c; };

int gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  while(b) {
    int c = a;
    a = b;
    b = c % b;
  }
  return a;
}

// Line = {a,b,c} such that a*x + b*y + c = 0
Line getLine(Point p1, Point p2) {
  int a = p1.y - p2.y;
  int b = p2.x - p1.x;
  int c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
  int sgn = (a < 0 || (a == 0 && b < 0)) ? -1 : 1;
  int f = gcd(a, gcd(b, c)) * sgn;
  a /= f;
  b /= f;
  c /= f;
  return {a, b, c};
}

/* ======================== */
/* Point - Segment distance */
/* ======================== */

// get distance between p and truncated projection of p on segment s -> e
double point_segment_dist(const Point& p, const Point& s, const Point& e) {
  if (s==e) return (p-s).norm(); // segment is a single point
  double t = min(1.0, max(0.0, (p-s).dot(e-s) / (e-s).norm2()));
  return (s+(e-s)*t-p).norm();
}

/* ===================== */
/* Point - Line distance */
/* ===================== */

// get distance between p and projection of p on line <- a - b ->
double point_line_dist(const Point& p, const Point& a, const Point& b) {
  double t = (p-a).dot(b-a) / (b-a).norm2();
  return (a+(b-a)*t-p).norm();
}