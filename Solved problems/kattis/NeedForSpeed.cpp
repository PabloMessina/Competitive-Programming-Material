// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
int N; double T;
double dist[1000], speed[1000];
double total_time(double c) {
    double t = 0;
    rep(i,0,N-1) t += dist[i] / (c + speed[i]);
    return t;
}
int main() {
    // read input
    cin >> N >> T;
    rep(i,0,N-1) cin >> dist[i] >> speed[i];
    // find best answer in range [l,r] using binary search
    double l = -*min_element(speed, speed+N);
    double r = 1001000.0;
    rep(_,1,100) {
        double m = (l+r)*0.5;
        if (total_time(m) > T) l = m;
        else r = m;
    }
    cout << setprecision(20) << fixed << (l+r)*0.5 << '\n';
    return 0;
}