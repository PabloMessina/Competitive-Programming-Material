// TODO: finish this
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXN = 100000;
int N;
double S[MAXN], V[MAXN];
double f(double t) {
    double maxx = max(t - S[0], 0.) * V[0];
    double minx = maxx;
    rep(i,1,N) {
        double x = max(t - S[i], 0.) * V[i];
        maxx = max(maxx, x);
        minx = min(minx, x);
    }
    return maxx - minx;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cout << setprecision(5) << fixed;
    while (cin >> N and N) {
        rep(i,0,N) cin >> S[i] >> V[i];
        double l = *max_element(S, S+N);
        double r = 1e5;
        double fl = f(l);
        while (f(r) < fl) r *= 2.0;
        rep(_,0,40) {
            double d = (r-l)/3.0;
            double m1 = l+d;
            double m2 = r-d;
            if (f(m1) < f(m2)) r = m2;
            else l = m1;
        }
        cout << f(0.5*(l+r)) << '\n';
    }
    return 0;
}