// tags: ternary search
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const double PI = acos(-1);
double b, c;
double f(double x) {
    return (x * x + b * x + c) / sin(x);
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    cout << fixed << setprecision(10);
    int t; cin >> t;
    while (t--) {
        cin >> b >> c;
        double l = 0;
        double r = PI * 0.5;
        rep(_,0,100) {
            double d = (r-l)/3.0;
            double m1 = l + d;
            double m2 = r - d;
            if (f(m1) <= f(m2)) r = m2;
            else l = m1;
        }
        cout << f(0.5 * (l+r)) << '\n';
    }
    return 0;
}