// tags: geometry, cross product
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
typedef long long int ll;
// -------------------------------
// references:
// https://github.com/PabloMessina/Competitive-Programming-Material/blob/master/Geometry/Geometry2DUtils.cpp
// https://www.geeksforgeeks.org/orientation-3-ordered-points/
struct Point { ll x, y; };
ll cross(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dy0 * dx1;
}
int main() {
    Point a, b; int n;
    cin >> a.x >> a.y >> b.x >> b.y >> n;
    while (n--) {
        Point p; cin >> p.x >> p.y;
        ll tmp = cross(a, b, p);
        // ternary operator: https://www.cprogramming.com/reference/operators/ternary-operator.html
        char ans = tmp > 0 ? 'I' : tmp < 0 ? 'D' : 'C';
        cout << ans << endl;
    }
    return 0;
}