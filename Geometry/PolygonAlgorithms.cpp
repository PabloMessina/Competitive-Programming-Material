#include <bits/stdc++.h>
#define rep(i,a,b) for(int i = a; i <= b; ++i)

// ----- Utils ------
struct Point {
    ll x, y;
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    ll cross(const Point& p) const { return x*p.y - y*p.x; }
};
ll cross(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}
int orientation(Point& a, Point& b, Point& c) {
    ll tmp = cross(a,b,c);
    return tmp < 0 ? -1 : tmp == 0 ? 0 : 1; // sign
}

/* ======================================== */
/* Area of 2D non self intersecting Polygon */
/* ======================================== */
//based on Green's Theorem:
//http://math.blogoverflow.com/2014/06/04/greens-theorem-and-area-of-polygons/
// ** points must be sorted ccw or cw
double polygon_area(vector<Point>& pol) {
    int n = pol.size()
    double area = 0;
    for (int i = n-1, j = 0; j < n; i = j++) {
        area += (pol[i].x + pol[j].x) * (pol[j].y - pol[i].y);
    }
    return area * 0.5; // use abs(area * 0.5) if points are cw
}

/* ================ */
/* Point in Polygon */
/* ================ */

// -----------------------------
// 1) Convex Polygons

// 1.1) O(N) method
bool point_in_convexhull(Point& p, vector<Point>& ch) {
    int n = ch.size();
    for (int i=n-1, j=0; j<n; i=j++) {
        if (cross(ch[i], ch[j], p) < 0) return false;
    }
    return true;
}

// 1.2) O(log N) method
bool point_in_triangle(Point& a, Point& b, Point& c, Point& x) {
    return cross(a, b, x) >= 0 and cross(b, c, x) >= 0 and cross(c, a, x) >= 0;
}
bool point_in_convexhull(Point& p, vector<Point>& ch) {
    if (cross(ch[0], ch[1], p) < 0) return false;
    if (cross(ch[0], ch.back(), p) > 0) return false;
    int l = 2, r = ch.size() - 1;
    while (l < r) {
        int m = (l+r) >> 1;
        if (cross(ch[0], ch[m], p) <= 0) r = m;
        else l = m+1;
    }
    return point_in_triangle(ch[0], ch[l-1], ch[l], p);
}

// ----------------------------------------------
// 2) General methods: for complex / simple polygons

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


/* ==================================== */
/* Find extreme point in Convex Polygon */
/* ==================================== */

int inline prev(int i, int n) { return i == 0 ? n-1 : i-1; }
int inline next(int i, int n) { return i == n-1 ? 0 : i+1; }
struct SignComp {
    vector<Point>* ch; Point d; int n;
    SignComp(vector<Point > *ch, Point d) : ch(ch), d(d) { n = ch->size(); }
    int operator()(int i, int j) {
        ll tmp = d.cross((*ch)[j] - (*ch)[i]);
        return tmp > 0 ? 1 : tmp == 0 ? 0 : -1;
    }
    bool is_extreme(int i, int& io) {
        return (io = (*this)(i, next(i,n))) >= 0 and (*this)(i, prev(i,n)) > 0;
    }
};

int extreme_point_index(Point& a, Point& b, vector<Point>& ch) {    
    Point d = b - a;
    SignComp cmp(&ch, d);
    int n = ch.size();
    int l = 0, r = n - 1, lo, mo;
    if (cmp.is_extreme(0, lo)) return 0;
    while (l + 1 < r) {
        int m = (l+r) >> 1;
        if (cmp.is_extreme(m, mo)) return m;
        if (lo != mo ? lo < mo : cmp(m, l) == lo) r = m;
        else l = m, lo = mo;
    }
    return cmp.is_extreme(l, lo) ? l : r;
}

pair<int,int> find_crossing_edge(Point& a, Point& b, vector<Point>& ch, int start, int end) {
    int o_ref = orientation(a, b, ch[start]);
    int n = ch.size();
    int l = start, r = start + ((end - start + n) % n);
    while (l < r) {
        int m = (l+r) >> 1;
        if (orientation(a, b, ch[m % n]) != o_ref) r = m;
        else l = m+1;
    }
    return { ((l-1+n) % n, l%n) };
}