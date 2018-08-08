// tags: geometry 2D, two pointers, dot product, calculus, derivatives
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

struct Point {
    double x, y;
    Point operator-(const Point& p) const { return {x - p.x, y - p.y}; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y}; }
    Point operator*(double c) const { return {x*c, y*c}; }
    double dot(const Point& p) const { return x*p.x + y*p.y; }
    double norm() const { return sqrt(x * x + y * y); }
    double norm2() const { return x * x + y * y; }
};

const int MAXN = 100000;
int N,M;
Point pts_a[MAXN], pts_b[MAXN];

// computes the minimum distance between segments a->b and c->d
// assuming that:
// 1) their traveled at the same speed
// 2) the segments have the same length, i.e (b-a).norm() == (d-c).norm()
// basically we minimize the function:
//    f(t) = ((a + (b-a) * t) - (c + (d-c) * t)).norm2(), with 0 <= t <= 1
//    which is a quadratic function, whose derivate is linear
double min_dist(Point& a, Point& b, Point& c, Point& d) {
    Point u = a - c;
    Point v = ((b-a) - (d-c));
    double v_norm2 = v.norm2();
    if (v_norm2 < 1e-10) return u.norm(); // almost zero (to handle precision noise)
    double t = - u.dot(v) / v_norm2;
    if (t < 0) t = 0;
    if (t > 1) t = 1;
    return (u + v * t).norm();
}

int main() {
    // read input
    scanf("%d", &N);
    rep(i,0,N-1) {
        double x, y; scanf("%lf%lf", &x, &y);
        pts_a[i] = {x,y};
    }
    scanf("%d", &M);
    rep(i,0,M-1) {
        double x, y; scanf("%lf%lf", &x, &y);
        pts_b[i] = {x,y};
    }
    // find optimum with 2 pointers
    Point cur_pos_a = pts_a[0];
    Point cur_pos_b = pts_b[0];
    int ia = 1, ib = 1;
    double ans = 1e9;
    while (ia < N and ib < M) {
        Point dir_a = pts_a[ia] - cur_pos_a;
        Point dir_b = pts_b[ib] - cur_pos_b;
        double lena = dir_a.norm();
        double lenb = dir_b.norm();
        double len = min(lena, lenb);
        Point next_pos_a = cur_pos_a + dir_a * (len / lena);
        Point next_pos_b = cur_pos_b + dir_b * (len / lenb);
        ans = min(ans, min_dist(cur_pos_a, next_pos_a, cur_pos_b, next_pos_b));
        if (lena == len) ia++;
        if (lenb == len) ib++;
        cur_pos_a = next_pos_a;
        cur_pos_b = next_pos_b;
    }
    printf("%.20lf\n", ans);
    return 0;
}