// tags: binary search
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// --------------------------------------
const int MAXN = 500000;
int N;
double pos[MAXN], vel[MAXN];

bool collision(double t) {
    double maxr = -1e18;
    rep(i,0,N) {
        if (vel[i] > 0)  maxr = max(maxr, pos[i] + vel[i] * t);
        else if (maxr > pos[i] + vel[i] * t) return true;
    }
    return false;
}

int main() {
    scanf("%d", &N); // printf/scanf because cin/cout gives TLE
    double r_minpos = 2e9, l_maxpos = -2e9;
    rep(i,0,N) {
        scanf("%lf %lf", &pos[i], &vel[i]);
        if (vel[i] > 0) r_minpos = min(r_minpos, pos[i]);
        else l_maxpos = max(l_maxpos, pos[i]);
    }
    if (r_minpos > l_maxpos) puts("-1");
    else {
        double tl = 0, tr = 1e9, tm;
        rep(_,0,70) {
            tm = 0.5*(tl+tr);
            if (collision(tm)) tr = tm;
            else tl = tm;
        }
        printf("%.20lf\n", 0.5*(tl+tr));
    }
    return 0;
}