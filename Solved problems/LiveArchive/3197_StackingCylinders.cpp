// tags: math, trigonometry, geometry
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
const double PI = acos(-1);
const int MAXN = 11;

struct Point {
    double x, y;
    bool operator<(const Point& o) const { return x < b.x; }
};
int n;
Point pts[MAXN];

int main() {
    while(true) {
        scanf("%d",&n);
        if(n==0) break;
        rep(i,0,n-1) {
            scanf("%lf", &pts[i].x);
            pts[i].y = 1.0;
        }
        sort(pts, pts+n);
        invrep(k,n,2) {
            rep(i, 0, k-2) {
                double dx = pts[i+1].x - pts[i].x;
                double dy = pts[i+1].y - pts[i].y;
                double d = sqrt(dx * dx + dy * dy);
                double alpha = acos(d * 0.25);
                double theta = abs(atan2(dy, dx));
                double mx = 2 * cos(alpha + theta);
                double my = 2 * sin(alpha + theta);
                if (dy >= 0) {
                    pts[i].x = pts[i].x + mx;
                    pts[i].y = pts[i].y + my;
                } else {
                    pts[i].x = pts[i+1].x - mx;
                    pts[i].y = pts[i+1].y + my;
                }
            }
        }
        printf("%.4lf %.4lf\n",pts[0].x, pts[0].y);
    }
    return 0;
}