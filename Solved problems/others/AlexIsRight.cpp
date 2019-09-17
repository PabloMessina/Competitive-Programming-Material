// tags: geometry, cross product, trigonometry, calculus
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// -------------------------------
const double R = 6371.0;
const double PI = acos(-1);

double to_radian(double angle) {
    return angle * PI/180.0;
}

struct Point {
    double x,y,z;
    static Point from_sphere_coords(double r, double u, double v) {
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
    double dot(Point& o) {
        return x*o.x + y*o.y + z*o.z;
    }
    double norm() {
        return sqrt(x*x + y*y + z*z);
    }
    Point unit() {
        double d = norm();
        return {x/d,y/d,z/d};
    }
    Point operator*(double k) const {
        return {x*k, y*k, z*k};
    }
    Point operator+(const Point& o) const {
        return {x+o.x, y+o.y, z+o.z};
    }
    Point operator-(const Point& o) const {
        return {x-o.x, y-o.y, z-o.z};
    }
};

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cout << setprecision(6) << fixed;
    int T; cin >> T;
    Point NP = Point::from_sphere_coords(R,PI/2,0);
    while (T--) {
        double u0, v0, u1, v1;
        cin >> u0 >> v0 >> u1 >> v1;
        u0 = to_radian(u0);
        v0 = to_radian(v0);
        u1 = to_radian(u1);
        v1 = to_radian(v1);
        Point p0 = Point::from_sphere_coords(R,u0,v0);
        Point p1 = Point::from_sphere_coords(R,u1,v1);

        double min_dist = min((p0-NP).norm(), (p1-NP).norm());

        Point axis = p0.cross(p1);
        double max_angle = acos(p0.dot(p1)/(R*R));
        Point p0_T = axis.cross(p0);
        Point p0_hat = p0.unit();
        Point p0_T_hat = p0_T.unit();
        double A = p0_T_hat.dot(NP);
        double B = -p0_hat.dot(NP);
        double t = atan(-A/B);
        if (t < 0) t += PI; // <- this is key

        if (0 < t and t < max_angle) {
            double tmp = ((p0_hat*cos(t) + p0_T_hat*sin(t))*R - NP).norm();
            if (tmp < min_dist) {
                min_dist = tmp;
                cout << "Alex\n";
            } else {
                cout << "Timothy\n";
            }
        } else {
            cout << "Timothy\n";
        }
        cout << min_dist << "\n\n";
    }
    return 0;
}