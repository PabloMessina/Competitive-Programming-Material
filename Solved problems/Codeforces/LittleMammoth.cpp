// WARNING: it gives either WA or TLE
// TODO: solve this problem using green's theorem
#include <bits/stdc++.h> // import everything in one shot
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

double cx,cy,r2,xl,xr,yu,yd;

double func_up(double x) {
    double dx = x - cx;
    return min(cy + sqrt(r2 - dx*dx), yu);
}

double func_down(double x) {
    double dx = x - cx;
    return max(cy - sqrt(r2 - dx*dx), yd);
}

double simpsons(double ya, double ym, double yb) {
    return (ya + 4. * ym + yb) / 6.;
}

double integrate(double xmin, double xmax, int steps) {
    double step = (xmax - xmin) / steps;
    double halfstep = 0.5 * step;
    double ya_up = func_up(xmin);
    double ya_down = func_down(xmin);
    double area = 0;
    rep(i,1,steps) {
        double xb = xmin + step * i;
        double xm = xb - halfstep;
        double yb_up = func_up(xb);
        double yb_down = func_down(xb);
        double ym_up = func_up(xm);
        double ym_down = func_down(xm);        
        double y_up = simpsons(ya_up, ym_up, yb_up);
        double y_down = simpsons(ya_down, ym_down, yb_down);
        if (y_up > y_down) area += step * (y_up - y_down);
        ya_up = yb_up;
        ya_down = yb_down;
    }
    return area;
}

int main() {
    double x1,y1,x2,y2,r;
    int i = 0;
    while (cin >> cx >> cy >> r >> x1 >> y1 >> x2 >> y2) {
        r2 = r * r;
        xl = min(x1, x2);
        xr = max(x1, x2);
        yd = min(y1, y2);
        yu = max(y1, y2);
        double xmin = max(cx - r, xl);
        double xmax = min(cx + r, xr);
        double ymin = max(cy - r, yd);
        double ymax = min(cy + r, yu);
        if (i++) cout << endl;
        if (xmin >= xmax or ymin >= ymax) {
            cout << 0 << endl;
        } else {
            cout << fixed;
            cout << setprecision(20);
            cout << integrate(xmin, xmax, (int)(xmax - xmin) * 8000) << endl;
        }
    }
    return 0;
}