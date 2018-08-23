// tags: math, trigonometry
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
typedef long long int ll;
const double PI = acos(-1);

int main() {
    double D, H;
    double a, b, c;
    scanf("%lf%lf", &D, &H);
    while (true) {
        scanf("%lf%lf%lf",&a,&b,&c);
        if (a <= 0 || b <= 0 || c <= 0) break;
        a *= PI / 180;
        b *= PI / 180;
        c *= PI / 180;
        double auxa = 1 / (tan(a) * tan(a));
        double auxb = 1 / (tan(b) * tan(b));
        double auxc = 1 / (tan(c) * tan(c));
        double aux = round(sqrt(2 * D * D / (auxa + auxc - 2 * auxb)) + H);
        ll ans = (ll) aux;
        printf("%lld\n", ans);
    }
    return 0;
}