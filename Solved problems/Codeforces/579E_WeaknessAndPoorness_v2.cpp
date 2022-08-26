// tags: binary search, DP (maximum subarray sum - Kadane's algorithm)
// Kadane's algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
//---------------
const int MAXN = 200000;
double a[MAXN];
int N;
bool increasing(double x, double& maxsum) {
    double last_maxp, last_maxn, maxp, maxn;
    last_maxp = last_maxn = maxp = maxn = 1e-18;
    rep(i,0,N) {
        last_maxp = max(last_maxp + a[i] - x, a[i] - x);
        maxp = max(maxp, last_maxp);
        last_maxn = max(last_maxn + x - a[i], x - a[i]);
        maxn = max(maxn, last_maxn);
    }
    maxsum = max(maxn, maxp);
    return maxn > maxp;
}
int main() {
    cin >> N;
    rep(i,0,N) cin >> a[i];
    double l = -1e4, r = 1e4;
    double ans;
    rep(_,0,100) {
        double m = (l+r)*0.5;
        if (increasing(m, ans)) r = m;
        else l = m;
    }
    cout << setprecision(20) << fixed << ans << '\n';
    return 0;
}