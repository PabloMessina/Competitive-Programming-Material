#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

const int MAXN = (int)(3*1e5);
const int MAXM = 1500;

struct Line { int a, b, c; };
struct Point {int x, y; };
struct Circle {int x, y, r; };
int n, m;
vector<Point> rightEnds[MAXN];
vector<Point> leftEnds[MAXN];
Circle circles[MAXM];

bool operator<(const Line& l1, const Line& l2) {
  if (l1.a != l2.a)
    return l1.a < l2.a;
  if (l1.b != l2.b)
    return l1.b < l2.b;
  return l1.c < l2.c;
}
bool operator<(const Point& p1, const Point& p2) {
  if (p1.x != p2.x)
    return p1.x < p2.x;
  return p1.y < p2.y;
}

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

inline int pow2(int x) { return x * x; }

inline int sqr_dist(Circle& c1, Circle& c2) {
  return pow2(c1.x - c2.x) + pow2(c1.y - c2.y);
}

int main() {
  scanf("%d%d", &n, &m);
  map<Line, int> toId;
  int trc = 0;
  
  // read segments
  rep (i, 1, n) {
    int x1, y1, x2, y2;
    scanf("%d%d%d%d",&x1, &y1, &x2, &y2);
    Point p1 = {2 * x1, 2 * y1};
    Point p2 = {2 * x2, 2 * y2};
    if (p2 < p1)
      swap(p1, p2);

    Line line = getLine(p1, p2);

    auto ans = toId.insert({line, trc});
    int idx = ans.first->second;
    if (ans.second)  trc++;

    leftEnds[idx].push_back(p1);
    rightEnds[idx].push_back(p2);
  }
  // sort segment ends groups
  rep (i,0, trc-1) {
    sort(leftEnds[i].begin(), leftEnds[i].end());
    sort(rightEnds[i].begin(), rightEnds[i].end());
  }
  // read circles
  rep (i, 0, m-1) {
    Circle* c = &circles[i];
    scanf("%d%d%d", &c->x, &c->y, &c->r);
  }
  // find owls
  int ans = 0;
  Circle c1, c2;
  rep (i, 0, m-2) {
    c1 = circles[i];
    rep (j, i+1, m-1) {
      c2 = circles[j];

      // same radius
      if (c1.r != c2.r)
        continue;

      // no intersection
      if (sqr_dist(c1, c2) <= pow2(c1.r + c2.r))
        continue;

      // check segment group exists
      Point pmid = { c1.x + c2.x, c1.y + c2.y };
      Point pend = { c1.x + c2.x + 2 * (c1.y - c2.y), c1.y + c2.y + 2 * (c2.x - c1.x) };
      Line line = getLine(pmid, pend);
      auto it = toId.find(line);
      if (it == toId.end())
        continue;

      int idx = it->second;
      ans += leftEnds[idx].size();
      ans -= lower_bound(rightEnds[idx].begin(), rightEnds[idx].end(), pmid) - rightEnds[idx].begin();
      ans -= leftEnds[idx].end() - upper_bound(leftEnds[idx].begin(), leftEnds[idx].end(), pmid);
    }
  }
  // answer
  printf("%d\n", ans);
  return 0;
}