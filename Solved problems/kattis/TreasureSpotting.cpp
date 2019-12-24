// tags: geometry, cross product, dot product
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int W, P;
template<typename T> struct Point { // 2D
    T x, y;
    Point<T> operator-(const Point<T>& p) const { return {x-p.x, y-p.y}; }
    T norm2() { return x*x + y*y; }
    T dot(const Point<T>& p) const { return x*p.x + y*p.y; }
    T cross(const Point<T>& p) const { return x*p.y - y*p.x; }
    int quadrant() const { // 0, 1, 2, 3
        if (x >= 0) return y >= 0 ? 0: 3;
        return y >= 0 ? 1 : 2;
    }
    bool operator<(const Point<T>& p) const { // smaller quadrant or same quadrant and to the right
        int q = quadrant();
        int qp = p.quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
    bool same_angle(const Point<T>& p) const { // two vectors pointing to the same direction
        return quadrant() == p.quadrant() and cross(p) == 0;
    }
};

ll cross(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    return (b - a).cross(c - a);
}
int orientation(Point<ll>& a, Point<ll>& b, Point<ll>& c) {
    ll tmp = cross(a,b,c);
    return tmp < 0 ? -1 : tmp == 0 ? 0 : 1; // sign
}
bool do_rectangles_intersect(Point<ll>& dl1, Point<ll>& ur1, Point<ll>& dl2, Point<ll>& ur2) {
    return max(dl1.x, dl2.x) <= min(ur1.x, ur2.x) && max(dl1.y, dl2.y) <= min(ur1.y, ur2.y);
}
bool do_segments_intersect(Point<ll>& p1, Point<ll>& q1, Point<ll>& p2, Point<ll>& q2) {
    int o11 = orientation(p1, q1, p2);
    int o12 = orientation(p1, q1, q2);
    int o21 = orientation(p2, q2, p1);
    int o22 = orientation(p2, q2, q1);
    if (o11 != o12 and o21 != o22) // general case -> non-collinear intersection
        return true;
    if (o11 == o12 and o11 == 0) { // particular case -> segments are collinear
        Point<ll> dl1 = {min(p1.x, q1.x), min(p1.y, q1.y)};
        Point<ll> ur1 = {max(p1.x, q1.x), max(p1.y, q1.y)};
        Point<ll> dl2 = {min(p2.x, q2.x), min(p2.y, q2.y)};
        Point<ll> ur2 = {max(p2.x, q2.x), max(p2.y, q2.y)};
        return do_rectangles_intersect(dl1, ur1, dl2, ur2);
    }
    return false;
}

struct Segment { Point<ll> a, b; };

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> W >> P;
    Point<ll> T; cin >> T.x >> T.y;
    vector<Segment> pirates;
    vector<Segment> walls;
    rep(i,0,W) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        walls.push_back({{x1,y1}, {x2,y2}});
    }
    rep(i,0,P) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        pirates.push_back({{x1,y1}, {x2,y2}});
    }
    rep(i,0,P) {
        auto& p = pirates[i];
        Point<ll> dir = p.b - p.a;
        Point<ll> t_rel = T - p.a;
        if (t_rel.norm2() > dir.norm2() or dir.dot(t_rel) < 0) {
            cout << "not visible\n";
            goto next;
        }
        for (auto& w : walls) {
            if (do_segments_intersect(p.a, T, w.a, w.b)) {
                cout << "not visible\n";
                goto next;
            }
        }
        rep(j,0,P) {
            if (j == i) continue;
            auto& p2 = pirates[j];
            Point<ll> p2_rel = p2.a - p.a;
            if (p2_rel.same_angle(t_rel) and p2_rel.norm2() <= t_rel.norm2()) {
                cout << "not visible\n";
                goto next;
            }
        }
        cout << "visible\n";
        next:;
    }
    return 0;
}