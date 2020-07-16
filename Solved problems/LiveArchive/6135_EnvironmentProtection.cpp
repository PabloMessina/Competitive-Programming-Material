// tags: binary search, numerical integration
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int N_BINS = 10000;
int W,D,A,K;
int p1[10], q1[10], p2[10], q2[10];
double ys1[N_BINS];
double ys2[N_BINS];

double func(double x, int* p, int* q) {
    double _x = x;
    double a = p[0], b = q[0];
    rep(i,1,K+1) {
        a += p[i] * _x;
        b += q[i] * _x;
        _x *= x;
    }
    return a / b;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while (cin >> W >> D >> A >> K) {
        rep(i,0,K+1) cin >> p1[i];
        rep(i,0,K+1) cin >> q1[i];
        rep(i,0,K+1) cin >> p2[i];
        rep(i,0,K+1) cin >> q2[i];

        double y1a = func(0, p1, q1);
        double y2a = func(0, p2, q2);
        double y1b, y2b, y1m, y2m, x;
        double bin_width = (double)W / N_BINS;

        rep(i,1,N_BINS+1) {
            x = bin_width * i;
            y1b = func(x, p1, q1);
            y1m = func(x - 0.5 * bin_width, p1, q1);
            ys1[i-1] = (y1a + 4 * y1m + y1b) / 6;
            y1a = y1b;

            y2b = func(x, p2, q2);
            y2m = func(x - 0.5 * bin_width, p2, q2);
            ys2[i-1] = (y2a + 4 * y2m + y2b) / 6;
            y2a = y2b;
        }

        double min_d = -D, max_d = 0.0;
        rep(t,0,100) {
            double mid_d = (min_d + max_d) * 0.5;
            double area = 0;            
            rep(i,0,N_BINS) {
                if (ys1[i] > mid_d) {
                    area += (ys1[i] - max(ys2[i], mid_d));
                }                
            }
            area *= bin_width;
            if (area >= A) min_d = mid_d;
            else max_d = mid_d;
        }
        cout << setprecision(5) << fixed << (0.5 * fabs(min_d + max_d)) << '\n';
    }
    return 0;
}