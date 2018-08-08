// tags: geometry 2D, point segment distance, dot product
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
    Point operator-(const Point& p) const { return {x - p.x, y - p.y }; }
    Point operator+(const Point& p) const { return {x + p.x, y + p.y }; }
    Point operator*(double d) const { return {x * d, y * d }; }
    double dot(const Point& p) const { return x * p.x + y * p.y; }
    double norm2() const { return x * x + y * y; }
    double norm() const { return sqrt(x * x + y * y); }
};
const int MAXN = 16;
int N;
Point pts[MAXN];

bool peekAndCheck(char c) {
    char c2 = getchar();
    ungetc(c2, stdin); // return char to stdin
    return c == c2;
}

double point_segment_dist(Point& p, Point& a, Point& b) {
    Point d = b-a;
    double t = d.dot(p-a) / d.norm2();
    if (t <= 0) return (p-a).norm();
    if (t >= 1) return (p-b).norm();
    return (a + d * t - p).norm();
}

int main() {
    while (true) {
        if (peekAndCheck('*')) break;
        scanf("%d\n", &N);
        Point c; scanf("%lf%lf\n", &c.x, &c.y);
        rep(i,0,N-1) { Point& p = pts[i]; scanf("%lf%lf\n", &p.x, &p.y); }
        double ans = 1e9;
        for (int i = 0, j = N-1; i < N; j=i++) {
            ans = min(ans, point_segment_dist(c, pts[i], pts[j]));
        }
        printf("%.3lf\n", ans);
    }
    return 0;
}