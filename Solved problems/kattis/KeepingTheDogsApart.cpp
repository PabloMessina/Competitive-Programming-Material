// geometry, two pointers, point-segment distance
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

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

double segdist(const Point& s, const Point& e, const Point& p) {
  if (s==e) return (p-s).norm();
  double t = min(1.0, max(0.0, (p-s).dot(e-s) / (e-s).norm2()));
  return (s+(e-s)*t-p).norm();
}

int main() {
  int n,m;
  double x,y;

  scanf("%d", &n);
  vector<Point> a(n);
  rep(i,0,n-1) { scanf("%lf%lf", &x, &y); a[i] = {x,y}; }

  scanf("%d", &m);
  vector<Point> b(m);
  rep(i,0,m-1) { scanf("%lf%lf", &x, &y); b[i] = {x,y}; }

  Point cura = a[0], curb = b[0];
  double global_min = (cura - curb).norm();
  int ia = 1, ib = 1;

  while (ia < n && ib < m) {

    Point diff1 = cura - curb;
    Point mova = a[ia] - cura;
    Point movb = b[ib] - curb;
    double lena = mova.norm();
    double lenb = movb.norm();
    double len = min(lena, lenb);

    cura = cura + mova.unit() * len;
    curb = curb + movb.unit() * len;
    Point diff2 = cura - curb;

    double segmin = segdist(diff1, diff2, {0,0});
    global_min = min(global_min, segmin);

    if (lena < lenb) {
      cura = a[ia++];
    } else if (lenb < lena) {
      curb = b[ib++];
    } else {
      cura = a[ia++];
      curb = b[ib++];
    }

  }

  printf("%.20lf\n", global_min);

  return 0;
}
