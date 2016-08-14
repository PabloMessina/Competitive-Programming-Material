/* ================ */
/* Point in Polygon */
/* ================ */

#include <vector>
struct Point { float x, y; };

/* signed area of p0 with respect to (p1 -> p2) */
float isLeft(Point p0, Point p1, Point p2) {
  return (p1.x - p0.x) * (p2.y - p0.y)
    - (p2.x - p0.x) * (p1.y - p0.y);
}

// ----------------------------------------------
// General methods: for complex / simple polygons

/* Nonzero Rule (winding number) */
bool inPolygon_nonzero(Point p, vector<Point>& pts) {
  int wn = 0; // winding number
  Point prev = pts.back();
  rep (i, 0, (int)pts.size() - 1) {
    Point curr = pts[i];
    if (prev.y <= p.y) {
      if (p.y < curr.y && isLeft(p, prev, curr) > 0)
        ++ wn; // upward & left
    } else {
      if (p.y >= curr.y && isLeft(p, prev, curr) < 0)
        -- wn; // downward & right
    }
    prev = curr;
  }
  return wn != 0; // non-zero :)
}

/* EvenOdd Rule (ray casting - crossing number) */
bool inPolygon_evenodd(Point p, vector<Point>& pts) {
  int cn = 0; // crossing number
  Point prev = pts.back();
  rep (i, 0, (int)pts.size() - 1) {
    Point curr = pts[i];
    if (((prev.y <= p.y) && (p.y < curr.y)) // upward crossing
      || ((prev.y > p.y) && (p.y >= curr.y))) { // downward crossing
      // check intersect's x-coordinate to the right of p
      float t = (p.y - prev.y) / (curr.y - prev.y);
      if (p.x < prev.x + t * (curr.x - prev.x))
        ++cn;
    }
    prev = curr;
  }
  return (cn & 1); // odd -> in, even -> out
}