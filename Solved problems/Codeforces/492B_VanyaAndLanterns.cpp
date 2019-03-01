// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
double as[1000];
int main() {
    int n; double len;
    scanf("%d %lf", &n, &len);
    rep(i,0,n-1) scanf("%lf", as+i);
    sort(as, as + n);
    double dl=0, dr=1e9;
    rep(_,1,60) {
        double dm = (dl + dr) * 0.5;
        bool cover = !(as[0] - dm > 0 or as[n-1] + dm < len);
        if (cover) rep(i,0,n-2) {
            if (as[i] + dm < as[i+1] - dm) {
                cover = false;
                break;
            }
        }
        if (cover) dr = dm;
        else dl = dm;
    }
    printf("%.15lf\n", (dl+dr)*0.5);
    return 0;
}