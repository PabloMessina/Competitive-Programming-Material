// tags: geometry, radial sweep line, trigonometry, binary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const double PI = acos(-1);
const double eps = 1e-8;
int N;
struct Point {
    double x, y;
    double norm2() { return x * x + y * y; }
    double norm() { return sqrt(norm2()); }
    double angle() { return atan2(y, x); }
};
Point pts[10000];
double dist[10000];
double angle[10000];
double mindist;
double shifts[4] = { 0, PI * 0.5, PI, PI * 1.5 };

double correct_angle(double a) {
    while (a > PI) a -= 2*PI;
    while (a < -PI) a += 2*PI;
    return a;
}

void add_angle_pair(vector<pair<double,double>>& pairs, double a, double b) {
    a = correct_angle(a);
    b = correct_angle(b);
    if (a <= b) pairs.emplace_back(a, b);
    else {
        pairs.emplace_back(a, PI);
        pairs.emplace_back(-PI, b);
    }
}

bool possible(double r) {
    double r_diag = r * sqrt(2.);
    if (r_diag <= mindist + eps) return true;
    if (r >= mindist - eps) return false;
    vector<pair<double,double>> pairs;
    rep(i,0,N) {
        if (dist[i] >= r_diag) continue;
        double a = acos(r / dist[i]);
        rep(j,0,4) {
            double s = shifts[j];
            double x = s + angle[i] + a;
            double y = s + angle[i] + PI/2. - a;
            add_angle_pair(pairs, x, y);
        }
    }
    sort(pairs.begin(), pairs.end());
    double x = -PI;
    for (auto& p : pairs) {
        if (x < p.first) return true;
        x = max(x, p.second);
    }
    return x < PI;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    mindist = 2e9;
    rep(i,0,N) {
        cin >> pts[i].x >> pts[i].y;
        dist[i] = pts[i].norm();
        angle[i] = pts[i].angle();
        mindist = min(mindist, dist[i]);
    }
    double rmin = 0.01, rmax = 1e9+0.01;    
    rep(_,0,100) {
        double r = (rmin + rmax) * 0.5;
        if (possible(r)) rmin = r;
        else rmax = r;
    }
    cout << setprecision(4) << fixed;
    cout << (rmin + rmax) * 4.0 << '\n';
    return 0;
}