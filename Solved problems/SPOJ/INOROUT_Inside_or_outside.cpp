// tags: geometry 2D, cross product, point in convex polygon detection
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
struct Point { ll x, y; };

ll cross(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}

bool point_in_triangle(Point& a, Point& b, Point& c, Point& x) {
    return cross(a, b, x) >= 0 and cross(b, c, x) >= 0 and cross(c, a, x) >= 0;
}
bool point_in_convexhull(Point& p, vector<Point>& ch) {
    if (cross(ch[0], ch[1], p) < 0) return false;
    if (cross(ch[0], ch.back(), p) > 0) return false;
    int l = 2, r = ch.size() - 1;
    while (l < r) {
        int m = (l+r) >> 1;
        if (cross(ch[0], ch[m], p) <= 0) r = m;
        else l = m+1;
    }
    return point_in_triangle(ch[0], ch[l-1], ch[l], p);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int N,Q; cin >> N >> Q;
    vector<Point> ch(N);
    for (auto& p : ch) cin >> p.x >> p.y;
    while (Q--) {
        Point p; cin >> p.x >> p.y;
        if (point_in_convexhull(p, ch)) cout << "D\n";
        else cout << "F\n";
    }
    return 0;
}