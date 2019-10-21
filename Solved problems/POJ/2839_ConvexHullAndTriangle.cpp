// TODO: finish this, needs debugging
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
bool DEBUG = false;
const double eps = 1e-8;
int N, M;
template<typename T>
struct Point {
    T x, y;
    Point<T> operator-(const Point<T>& p) const {
        return {x - p.x, y - p.y};
    }
    Point<T> operator+(const Point<T>& p) const {
        return {x + p.x, y + p.y};
    }
    Point<T> operator*(T c) const {
        return {x * c, y * c};
    }
    Point<double> cast() {
        return { (double)x, (double)y };
    }
    T norm2() { return x*x + y*y; }
    bool operator<(const Point<T>& p) {
        return x < p.x || (x == p.x && y < p.y);
    }
};
struct Triangle { Point<ll> a, b, c; };
vector<Point<ll>> pts;
vector<Triangle> ts;
vector<double> ch_acc_area;

ll cross(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}
int orientation(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    ll tmp = cross(a, b, c); return tmp < 0 ? -1 : tmp == 0 ? 0 : 1;
}

vector<Point<ll>> convex_hull(vector<Point<ll>>& P) {
    int n = P.size(), k = 0;
    vector<Point<ll>> H(2*n);
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

bool point_in_convex_polygon(Point<ll>& p, vector<Point<ll>>& poly) {
    if (cross(poly[0], poly[1], p) < 0) return false;
    if (cross(poly[0], poly.back(), p) > 0) return false;
    int l = 2, r = poly.size() - 1;
    while (l < r) {
        int m = (l+r) >> 1;
        if (cross(poly[0], poly[m], p) <= 0) r = m;
        else l = m+1;
    }
    return point_in_triangle(poly[0], poly[l-1], poly[l], p);
}

pair<int,int> find_crossing_edge(Point<ll>& a, Point<ll>& b, vector<Point<ll>>& ch, int start, int end) {
    int o_ref = orientation(a, b, ch[start]);
    int n = ch.size();
    int l = start, r = start + ((end - start + n) % n);
    while (l < r) {
        int m = (l+r) >> 1;
        if (orientation(a, b, ch[m % n]) != o_ref) r = m;
        else l = m+1;
    }
    return {(l-1+n) % n, l%n};
}

ll determinant(Point<ll> a, Point<ll> b) {
    return a.x * b.y - a.y * b.x;
}

bool find_line_line_intersection(Point<ll>& a1, Point<ll>& b1, Point<ll>& a2, Point<ll>& b2,
        double& t1, double& t2) {
    auto d1 = b1 - a1;
    auto d2 = b2 - a2;
    auto _d2 = d2 * -1;
    ll detA = determinant(d1, _d2);
    if (detA == 0) return false;
    Point<ll> b = a2 - a1;
    t1 = (double)determinant(b, _d2)/(double)detA;
    t2 = (double)determinant(d1, b)/(double)detA;
    return true;
}

struct Intersection {
    pair<int,int> ch_edge;
    Point<double> p;
    bool exiting;
    Intersection(pair<int,int> ch_edge, Point<double> p, bool exiting) :
        ch_edge(ch_edge), p(p), exiting(exiting) {}
};

void process_segment_convexhull_intersection(Point<ll>& a, Point<ll>& b, vector<Point<ll>>& ch,
        vector<Intersection>& intersections) {
    if (DEBUG) {        
        printf("process_seg_ch_int:: a=(%lld,%lld), b=(%lld,%lld)\n", a.x,a.y, b.x,b.y);    
    }
    int o_ref, l, r, n;
    int i_ref = 0;
    while ((o_ref = orientation(a, b, ch[i_ref])) == 0) ++i_ref;
    if (DEBUG) {        
        printf("\ti_ref = %d, o_ref = %d   (ch[i_ref] = (%lld,%lld))\n", i_ref, o_ref, ch[i_ref].x, ch[i_ref].y);
    }
    n = ch.size();
    l = i_ref;
    r = i_ref + n - 1;
    while (l < r) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;
        int v1 = abs(orientation(a, b, ch[m1 % n]) - o_ref);
        int v2 = abs(orientation(a, b, ch[m2 % n]) - o_ref);
        if (v1 > v2) r = m2-1;
        else l = m1+1;
    }
    int i_max = l % n;
    int o_max = orientation(a, b, ch[i_max]);
    if (DEBUG) {        
        printf("\tl = %d, r = %d, ch.size() = %d\n", l, r, ch.size());
        printf("\ti_max = %d, o_max=%d (ch[i_max] = (%lld,%lld))\n", i_max, o_max, ch[i_max].x, ch[i_max].y);
    }
    if (o_ref == o_max) return;
    auto e1 = find_crossing_edge(a, b, ch, i_ref, i_max);
    auto e2 = find_crossing_edge(a, b, ch, i_max, i_ref);
    if (DEBUG) {        
        printf("\t ** e1 = {%d, %d}\n", e1.first, e1.second);
        printf("\t ** e2 = {%d, %d}\n", e2.first, e2.second);
    }
    assert (e1 != e2);
    assert (min(e1.first, e1.second) != min(e2.first, e2.second) or
            max(e1.first, e1.second) != max(e2.first, e2.second));
    double r1, s1, r2, s2;
    assert (find_line_line_intersection(a, b, ch[e1.first], ch[e1.second], r1, s1));
    assert (find_line_line_intersection(a, b, ch[e2.first], ch[e2.second], r2, s2));
    assert (-eps <= s1 and s1 <= 1.0 + eps);
    assert (-eps <= s2 and s2 <= 1.0 + eps);    
    if (DEBUG) {        
        printf("\t   r1 = %lf, s1 = %lf\n", r1, s1);
        printf("\t   r2 = %lf, s2 = %lf\n", r2, s2);
    }
    if (r1 > 1.0 - eps and r2 > 1.0 - eps) return;
    if (r1 < eps and r2 < eps) return;
    if (abs(r1 - r2) < eps) return;
    if (r1 > r2) {
        swap(r1, r2);
        swap(e1, e2);
        swap(s1, s2);
    }
    assert (r1 < r2);
    assert (max(r1, 0.) < min(r2, 1.));
    auto _a = a.cast();
    auto _ba = (b-a).cast();
    intersections.emplace_back(e1, _a + _ba * max(r1, 0.), false);
    intersections.emplace_back(e2, _a + _ba * min(r2, 1.), r2 < 1. + eps);
}

double segment_integral(const Point<double>& a, const Point<double>& b) {
    if (DEBUG) {        
        printf("seg_integral: a=(%lf,%lf) b=(%lf,%lf)\n", a.x,a.y, b.x,b.y);
    }
    return 0.5 * (a.x + b.x) * (b.y - a.y);
}

int edge_min_ccw(pair<int,int> e, int n) {
    if (DEBUG) {
        printf("edge_min_ccw: e = (%d,%d), n = %d\n", e.first, e.second, n);
    }
    if (abs(e.first - e.second) == 1) return min(e.first, e.second);
    assert (min(e.first, e.second) == 0 and max(e.first, e.second) == n-1);
    return n-1;
}
int edge_max_ccw(pair<int,int> e, int n) {
    if (DEBUG) {
        printf("edge_max_ccw: e = (%d,%d), n = %d\n", e.first, e.second, n);
    }
    if (abs(e.first - e.second) == 1) return max(e.first, e.second);
    assert (min(e.first, e.second) == 0 and max(e.first, e.second) == n-1);
    return 0;
}

double area_intersection(Triangle& t, vector<Point<ll>>& ch) {
    if (ch.size() <= 2) return 0;
    ll tmp = cross(t.a, t.b, t.c);
    if (tmp == 0) return 0;
    if (tmp < 0) swap(t.b, t.c);
    vector<Intersection> intersections;
    process_segment_convexhull_intersection(t.a, t.b, ch, intersections);
    process_segment_convexhull_intersection(t.b, t.c, ch, intersections);
    process_segment_convexhull_intersection(t.c, t.a, ch, intersections);
    int n = intersections.size();
    if (DEBUG) {
        printf("n = %d\n", n);
    }
    if (n == 0) {
        if (point_in_triangle(t.a, t.b, t.c, ch[0]) and
            point_in_triangle(t.a, t.b, t.c, ch[1]) and
            point_in_triangle(t.a, t.b, t.c, ch[2])) return ch_acc_area[ch.size()];
        return 0;
    }
    if (DEBUG) {        
        printf("intersections:\n");
        for (auto& i : intersections) {
            printf("\te=(%d,%d), p=(%lf,%lf), exiting=%s\n",
                i.ch_edge.first, i.ch_edge.second, i.p.x, i.p.y, i.exiting ? "out" : "in");
        }
        printf("---- computing area:\n");
    }
    double area = 0;
    for (int j = 0, i = n-1; j < n; i = j++) {
        auto& a = intersections[i];
        auto& b = intersections[j];
        if ((a.p - b.p).norm2() < eps) continue;
        if (a.exiting) {
            assert (!b.exiting);
            if (DEBUG) {
                printf("convexhull integral:\n");
                printf("\ta.ch_edge = (%d,%d)\n", a.ch_edge.first, a.ch_edge.second);
                printf("\tb.ch_edge = (%d,%d)\n", b.ch_edge.first, b.ch_edge.second);
            }
            int k1 = edge_min_ccw(a.ch_edge, ch.size());
            int k2 = edge_max_ccw(b.ch_edge, ch.size());
            if (DEBUG) {
                printf("\t   --> k1 = %d\n", k1);
                printf("\t   --> k2 = %d\n", k2);
            }
            if (k1 <= k2) {
                area += ch_acc_area[k2] - ch_acc_area[k1];
            } else {
                area += ch_acc_area[ch.size()] - (ch_acc_area[k1] - ch_acc_area[k2]);
            }
            if (DEBUG) {                
                printf("area = %lf\n", area);
            }
            area -= segment_integral(ch[k1].cast(), a.p);
            area -= segment_integral(b.p, ch[k2].cast());
            if (DEBUG) {
                printf("area = %lf\n", area);
            }
        } else {
            area += segment_integral(a.p, b.p);
            if (DEBUG) {
                printf("area = %lf\n", area);
            }
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
        auto& t = ts[i];
        cin >> t.a.x >> t.a.y;
        cin >> t.b.x >> t.b.y;
        cin >> t.c.x >> t.c.y;
    }
    vector<Point<ll>> ch = convex_hull(pts);
    if (DEBUG) {
        printf("convex hull:\n");
        for (auto& p : ch) {
            printf("\t(%lld, %lld)\n", p.x, p.y);
        }
    }
    int n = ch.size();
    ch_acc_area.assign(n + 1, 0);
    rep(i,1,n) ch_acc_area[i] = ch_acc_area[i-1] +
        segment_integral(ch[i-1].cast(), ch[i == n ? 0 : i].cast());
    if (DEBUG) {
        printf("ch_acc_area:\n");
        rep(i,0,n) {
            printf("\ti=%d, ch_acc_area=%lf\n", i, ch_acc_area[i]);
        }
    }
    // cout << setprecision(5) << fixed;
    cout << setprecision(0) << fixed;
    for (auto& t : ts) cout << area_intersection(t, ch) << '\n';
    return 0;
}