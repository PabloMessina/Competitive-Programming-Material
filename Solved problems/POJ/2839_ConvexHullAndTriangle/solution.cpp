// tags: geometry, convex hull, cross product, dot product, binary search adhoc,
// line intersection, polygon area, green's theorem
#include <cassert>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const long double eps = 1e-8L;
const long double ZERO = 0L;
const long double ONE = 1L;
int N, M;
template<typename T>
struct Point {
    T x, y;
    Point<T>() {}
    Point<T>(T x, T y) : x(x), y(y) {}
    Point<T> operator-(const Point<T>& p) const { return Point<T>(x - p.x, y - p.y); }
    Point<T> operator+(const Point<T>& p) const { return Point<T>(x + p.x, y + p.y); }
    Point<T> operator*(T c) const { return Point<T>(x * c, y * c); }
    T cross(const Point<T>& p) const { return x*p.y - y*p.x; }
    T dot(const Point<T>& p) const { return x*p.x + y*p.y; }
    Point<long double> cast() { return Point<long double>(x, y); }
    T norm2() { return x*x + y*y; }
    bool operator<(const Point<T>& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
struct Triangle { Point<ll> a, b, c; };
vector<Point<ll> > pts;
vector<Triangle> ts;
vector<long double> ch_acc_area;

ll cross(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}
int orientation(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    ll tmp = cross(a, b, c); return tmp < 0 ? -1 : tmp == 0 ? 0 : 1;
}

vector<Point<ll> > convex_hull(vector<Point<ll> >& P) {
    int n = P.size(), k = 0;
    vector<Point<ll> > H(2*n);
    sort(P.begin(), P.end());
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && cross(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    H.resize(k-1);
    return H;
}

bool point_in_triangle(Point<ll>& a, Point<ll>& b, Point<ll>& c, Point<ll>& x) {
    return cross(a, b, x) >= 0 and cross(b, c, x) >= 0 and cross(c, a, x) >= 0;
}

pair<int,int> find_crossing_edge(Point<ll>& a, Point<ll>& b, vector<Point<ll> >& ch, int start, int end) {
    int o_ref = orientation(a, b, ch[start]);
    int n = ch.size();
    int l = start, r = start + ((end - start + n) % n);
    while (l < r) {
        int m = (l+r) >> 1;
        if (orientation(a, b, ch[m % n]) != o_ref) r = m;
        else l = m+1;
    }
    return make_pair((l-1+n) % n, l%n);
}

ll det(Point<ll>& a, Point<ll>& b) { return a.x * b.y - a.y * b.x; }

bool find_line_line_intersection(Point<ll>& a1, Point<ll>& b1, Point<ll>& a2, Point<ll>& b2,
        long double& t1, long double& t2) {
    Point<ll> d1 = b1 - a1;
    Point<ll> d2 = b2 - a2;
    Point<ll> _d2 = d2 * -1;
    ll detA = det(d1, _d2);
    if (detA == 0) return false;
    Point<ll> b = a2 - a1;
    t1 = (long double)det(b, _d2)/(long double)detA;
    t2 = (long double)det(d1, b)/(long double)detA;
    return true;
}

struct Intersection {
    pair<int,int> ch_edge;
    Point<long double> p;
    bool exiting;
    Intersection(pair<int,int> ch_edge, Point<long double> p, bool exiting) :
        ch_edge(ch_edge), p(p), exiting(exiting) {}
};

int extreme_point_index(Point<ll>& a, Point<ll>& b, vector<Point<ll> >& ch) {
    int n = ch.size();
    Point<ll> v = b - a;
    v = Point<ll>(-v.y, v.x); // to find the leftmost point
    if (v.dot(ch[0]) >= v.dot(ch[1]) && v.dot(ch[0]) >= v.dot(ch[n - 1])) {
        return 0;
    }
    int l = 0, r = n;
    while (true) {
        int m = (l + r) / 2;
        if (v.dot(ch[m]) >= v.dot(ch[m + 1]) && v.dot(ch[m]) >= v.dot(ch[m - 1])) {
            return m;
        }
        int d1 = v.dot(ch[l + 1] - ch[l]) > 0;
        int d2 = v.dot(ch[m + 1] - ch[m]) > 0;
        int a = v.dot(ch[m]) > v.dot(ch[l]);
        if (d1) { if (d2 && a) l = m; else r = m; }
        else { if (!d2 && a) r = m; else l = m; }
    }
}

void process_segment_convexhull_intersection(Point<ll>& a, Point<ll>& b, vector<Point<ll> >& ch,
        vector<Intersection>& intersections) {
    int i1 = extreme_point_index(a, b, ch);
    int i2 = extreme_point_index(b, a, ch);    
    int o1 = orientation(a, b, ch[i1]);
    int o2 = orientation(a, b, ch[i2]);
    if (o1 == o2) return;
    pair<int,int> e1 = find_crossing_edge(a, b, ch, i1, i2);
    pair<int,int> e2 = find_crossing_edge(a, b, ch, i2, i1);
    long double r1, s1, r2, s2;
    assert (find_line_line_intersection(a, b, ch[e1.first], ch[e1.second], r1, s1));
    assert (find_line_line_intersection(a, b, ch[e2.first], ch[e2.second], r2, s2));
    if (r1 > 1.0 - eps and r2 > 1.0 - eps) return;
    if (r1 < eps and r2 < eps) return;
    if (abs(r1 - r2) < eps) return;
    if (r1 > r2) swap(r1, r2), swap(e1, e2), swap(s1, s2);
    Point<long double> _a = a.cast();
    Point<long double> _ba = (b-a).cast();
    intersections.push_back(Intersection(e1, _a + _ba * max(r1, ZERO), false));
    intersections.push_back(Intersection(e2, _a + _ba * min(r2, ONE), r2 < ONE + eps));
}

long double segment_integral(const Point<long double>& a, const Point<long double>& b) {
    return (a.x + b.x) * (b.y - a.y) * 0.5L;
}

int edge_min_ccw(pair<int,int> e, int n) {
    if (abs(e.first - e.second) == 1) return min(e.first, e.second);
    return n-1;
}
int edge_max_ccw(pair<int,int> e, int n) {
    if (abs(e.first - e.second) == 1) return max(e.first, e.second);
    return 0;
}

long double area_intersection(Triangle& t, vector<Point<ll> >& ch) {
    if (ch.size() <= 2) return 0;
    ll tmp = cross(t.a, t.b, t.c);
    if (tmp == 0) return 0;
    if (tmp < 0) swap(t.b, t.c);
    vector<Intersection> intersections;
    process_segment_convexhull_intersection(t.a, t.b, ch, intersections);
    process_segment_convexhull_intersection(t.b, t.c, ch, intersections);
    process_segment_convexhull_intersection(t.c, t.a, ch, intersections);
    int n = intersections.size();
    if (n == 0) {
        if (point_in_triangle(t.a, t.b, t.c, ch[0]) and
            point_in_triangle(t.a, t.b, t.c, ch[1]) and
            point_in_triangle(t.a, t.b, t.c, ch[2])) return ch_acc_area[ch.size()];
        return 0;
    }
    long double area = 0;
    for (int j = 0, i = n-1; j < n; i = j++) {
        Intersection& a = intersections[i];
        Intersection& b = intersections[j];
        if ((a.p - b.p).norm2() < eps) continue;
        if (a.exiting) {
            int k1 = edge_min_ccw(a.ch_edge, ch.size());
            int k2 = edge_max_ccw(b.ch_edge, ch.size());
            if (k1 < k2) {
                area += ch_acc_area[k2] - ch_acc_area[k1];
            } else {
                area += ch_acc_area[ch.size()] - (ch_acc_area[k1] - ch_acc_area[k2]);
            }
            area -= segment_integral(ch[k1].cast(), a.p);
            area -= segment_integral(b.p, ch[k2].cast());
        } else {
            area += segment_integral(a.p, b.p);
        }
    }
    return area;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    pts.resize(N);
    rep(i,0,N-1) cin >> pts[i].x >> pts[i].y;
    cin >> M;
    ts.resize(M);
    rep(i,0,M-1) {
        Triangle& t = ts[i];
        cin >> t.a.x >> t.a.y;
        cin >> t.b.x >> t.b.y;
        cin >> t.c.x >> t.c.y;
    }
    vector<Point<ll> > ch = convex_hull(pts);
    int n = ch.size();
    ch_acc_area.assign(n + 1, 0);
    rep(i,1,n) ch_acc_area[i] = ch_acc_area[i-1] +
        segment_integral(ch[i-1].cast(), ch[i == n ? 0 : i].cast());
    cout << setprecision(0) << fixed;
    for (vector<Triangle>::iterator it = ts.begin(); it != ts.end(); ++it)
        cout << (double)area_intersection(*it, ch) << '\n';
    return 0;
}