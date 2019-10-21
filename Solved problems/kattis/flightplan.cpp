// tags: geometry, dot product, cross product, trigonometry,
// spherical coordinates, arc parametrization
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const long double R = 6370;
const long double R2 = R*R;
const long double PI = acos(-1);
const long double EPS = 1e-8;
long double to_radian(long double angle) {
    return angle * PI/180.0;
}
struct Point {
    long double x,y,z;
    static Point from_sphere_coords(long double r, long double u, long double v) {
        return {
            r*cos(u)*cos(v),
            r*cos(u)*sin(v),
            r*sin(u)
        };
    }
    Point cross(Point& o) {
        return {
            y*o.z - z*o.y,
            z*o.x - x*o.z,
            x*o.y - y*o.x
        };
    }
    long double dot(Point& o) {
        return x*o.x + y*o.y + z*o.z;
    }
    long double norm() {
        return sqrt(x*x + y*y + z*z);
    }
    Point unit() {
        long double d = norm();
        return {x/d,y/d,z/d};
    }
    Point operator*(long double k) const {
        return {x*k, y*k, z*k};
    }
    Point operator+(const Point& o) const {
        return {x+o.x, y+o.y, z+o.z};
    }
    Point operator-(const Point& o) const {
        return {x-o.x, y-o.y, z-o.z};
    }
};
long double earth_angle_between(Point& a, Point& b) {
    return acos(a.dot(b)/R2);
}
bool point_in_arc(Point& a, Point& b, Point& n, Point& p) {
    long double angle_ab = earth_angle_between(a, b);
    long double angle_ap = earth_angle_between(a, p);
    if (angle_ap > angle_ab) return false;
    Point c_ = n.cross(a).unit();
    Point a_ = a.unit();
    Point a_rotated = (a_ * cos(angle_ap) + c_ * sin(angle_ap)) * R;
    return ((p - a_rotated).norm() < EPS);
}
bool find_arcs_intersection(Point& a1, Point& b1, Point& a2, Point& b2, long double& angle) {
    Point n1 = a1.cross(b1).unit();
    Point n2 = a2.cross(b2).unit();
    Point i = n1.cross(n2);
    if (i.norm() < EPS) return false;
    i = i.unit() * R;
    if (point_in_arc(a1, b1, n1, i) and point_in_arc(a2, b2, n2, i)) {
        angle = earth_angle_between(a1, i);
        return true;
    }
    i = i * -1.;
    if (point_in_arc(a1, b1, n1, i) and point_in_arc(a2, b2, n2, i)) {
        angle = earth_angle_between(a1, i);
        return true;
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int C; cin >> C;
    vector<vector<Point>> continents(C);
    for (auto& cont :  continents) {
        int n; cin >> n;
        while (n--) {
            long double phi, lamb; cin >> phi >> lamb;
            phi = to_radian(phi);
            lamb = to_radian(lamb);
            cont.push_back(Point::from_sphere_coords(R, phi, lamb));
        }
    }
    int M; cin >> M;
    vector<Point> flight_plan;
    rep(_, 1, M) {
        long double phi, lamb; cin >> phi >> lamb;
        phi = to_radian(phi);
        lamb = to_radian(lamb);
        flight_plan.push_back(Point::from_sphere_coords(R, phi, lamb));
    }
    long double full_length = 0;
    long double inside_length = 0;
    bool inside = true;
    rep(i,0,M-2) {
        auto& p1 = flight_plan[i];
        auto& p2 = flight_plan[i+1];
        long double angle_p1p2 = earth_angle_between(p1, p2);
        full_length += angle_p1p2;
        vector<long double> angles;
        long double angle;
        for (auto& cont : continents) {
            int n = cont.size();
            for (int i = n-1, j = 0; j < n; i = j++) {
                if (find_arcs_intersection(p1, p2, cont[i], cont[j], angle)) {
                    angles.push_back(angle);
                }
            }
        }
        if (angles.size() == 0) {
            if (inside) inside_length += angle_p1p2;
        } else {
            sort(angles.begin(), angles.end());
            long double prev_angle = 0;
            for (long double& angle : angles) {
                if (inside) {
                    inside_length += angle - prev_angle;
                }
                prev_angle = angle;
                inside = !inside;
            }
            if (inside) {
                inside_length += angle_p1p2 - prev_angle;
            }
        }
    }
    full_length *= R;
    inside_length *= R;
    cout << setprecision(20) << fixed;
    cout << (double)full_length << ' '
         << (double)(100. * (full_length - inside_length) / full_length) << '\n';
    return 0;
}