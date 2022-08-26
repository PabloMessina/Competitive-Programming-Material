// tags: binary search, DP (maximum subarray sum - Kadane's algorithm)
// Kadane's algorithm: https://en.wikipedia.org/wiki/Maximum_subarray_problem#Kadane's_algorithm
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
//---------------
const int MAXN = 200000;
double a[MAXN];
int N;

double f_naive(double x) {
    double ans = 0;
    rep(i,0,N) {
        rep(j,i,N) {
            double sum = 0;
            rep(k,i,j+1) sum += a[k];
            ans = max(ans, abs(sum));
        }
    }
    return ans;
}

double f(double x) {
    double max_pos = 0;
    double min_neg = 0;
    double max_here = -1e9;
    double min_here = 1e9;
    rep(i,0,N) {
        
    }
    return ans;
}

int main() {
    cin >> N;
    rep(i,0,N) cin >> a[i];
    double l = -1e4, r = 1e4;
    rep(_,0,100) {
        double d = (r - l) / 3.0;
        double m1 = l + d, m2 = r - d;
        double f1 = f(m1), f2 = f(m2);
        if (f1 <= f2) r = m2;
        if (f1 >= f2) l = m1;
    }
    double ans = f((l+r)*.5);
    cout << setprecision(20) << fixed << ans << '\n';
    return 0;
}