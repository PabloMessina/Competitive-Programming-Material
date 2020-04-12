// tags: ternary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
vector<double> S, D;
int N, K;
double f(double t) {
    double maxx = S[0] * t + D[0];
    double minx = maxx;
    rep(i,1,N) {
        double x = S[i] * t + D[i];
        maxx = max(maxx, x);
        minx = min(minx, x);
    }
    return maxx - minx;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cin >> N >> K;
    S.resize(N);
    D.resize(N);
    rep(i,0,N) cin >> S[i] >> D[i];
    double l = 0.0, r = K;
    rep(_,0,100) {
        double d = (r-l)/3.0;
        double m1 = l+d;
        double m2 = r-d;
        if (f(m1) < f(m2)) r = m2;
        else l = m1;
    }
    cout << setprecision(6) << fixed << f((l+r)*0.5) << '\n';
    return 0;
}