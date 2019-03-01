// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
double xs[60000];
double ms[60000];
int main() {
    double xl = 1e9, xr = 1;
    int n; scanf("%d", &n);
    rep(i,0,n-1) {
        scanf("%lf", xs+i);
        xl = min(xl, xs[i]);
        xr = max(xr, xs[i]);
    }
    rep(i,0,n-1) {
        double v; scanf("%lf", &v);
        ms[i] = 1 / v;
    }
    double tmax;
    rep(_,1,60) {
        double xm = (xl+xr) * 0.5;
        int i_max;
        tmax = 0;
        rep(i,0,n-1) {
            double t = fabs(xs[i] - xm) * ms[i];
            if (tmax < t) {
                tmax = t;
                i_max = i;
            }
        }
        if (xs[i_max] > xm) {
            xl = xm;
        } else {
            xr = xm;
        }
    }
    printf("%.15lf\n", tmax);
    return 0;
}