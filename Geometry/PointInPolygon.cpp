/* ================ */
/* Point in Polygon */
/* ================ */

#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; ++i)
struct Point { double x, y; };

// cross product (b - a) x (c - a)
double cross(Point& a, Point& b, Point& c) {
    double dx0 = b.x - a.x, dy0 = b.y - a.y;
    double dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}
int orientation(Point& a, Point& b, Point& c) {
    double tmp = cross(a,b,c);
    return tmp < 0 ? -1 : tmp == 0 ? 0 : 1; // sign
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
            if (p.y < curr.y && cross(prev, curr, p) > 0)
                ++ wn; // upward & left
        } else {
            if (p.y >= curr.y && cross(prev, curr, p) < 0)
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
            double t = (p.y - prev.y) / (curr.y - prev.y);
            if (p.x < prev.x + t * (curr.x - prev.x))
                ++cn;
        }
        prev = curr;
    }
    return (cn & 1); // odd -> in, even -> out
}

// -------------------------------------------------
// Convex Polygon method: check orientation changes
bool inConvexPolygon(Point& p, vector<Point>& pts) {
    int n = pts.size();
    int o_min = 0, o_max = 0;
    for (int i=0, j=n-1; i < n; j=i++) {
        int o = orientation(pts[j], pts[i], p);
        if (o == 1) o_max = 1;
        else if (o == -1) o_min = -1;
        if (o_max - o_min == 2) return false;
    }
    return true;
}