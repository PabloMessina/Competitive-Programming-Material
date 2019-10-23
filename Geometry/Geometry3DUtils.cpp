/* =========================== */
/* Example of Point Definition */
/* =========================== */
struct Point { // 3D
    double x, y, z;
    bool operator==(const Point& p) const { return x==p.x and y==p.y and z==p.z; }
    Point operator+(const Point& p) const { return {x+p.x, y+p.y, z+p.z}; }
    Point operator-(const Point& p) const { return {x-p.x, y-p.y, z-p.z}; }
    Point operator*(double d) const { return {x*d, y*d, z*d}; }
    double norm2() { return x*x + y*y + z*z; }
    double norm() { return sqrt(norm2()); }
    double dot(const Point& p) { return x*p.x + y*p.y + z*p.z; }
    Point cross(Point& p) {
        return {
            y*p.z - z*p.y,
            z*p.x - x*p.z,
            x*p.y - y*p.x
        };
    }
    Point unit() {
        double d = norm();
        return {x/d, y/d, z/d};
    }
    static Point from_sphere_coords(double r, double u, double v) {
        return {
            r*cos(u)*cos(v),
            r*cos(u)*sin(v),
            r*sin(u)
        };
    }
};
// compute angle (0 <= angle <= PI) between vectors a and b
// ** for better performance, the norms can be precomputed
//   or norms can be ommited altogether if a and b are unit vectors
double angle_between(Point& a, Point& b) {
    return acos(a.dot(b)/(a.norm() * b.norm()));
}
// check if point p belongs to the sphere arc from a to b.
// ** this assumes that a and b are points on a sphere centered at (0,0,0),
// and the sphere arc from a to b is the shortest path on the sphere connecting them
const double EPS = 1e-8;
bool point_in_arc(Point& a, Point& b, Point& p) {
    double angle_ab = angle_between(a, b);
    double angle_ap = angle_between(a, p);
    if (angle_ap > angle_ab) return false;
    Point n = a.cross(b);
    Point c_hat = n.cross(a).unit();
    double R = a.norm();
    Point a_hat = a * (1./R);
    Point a_rotated = (a_hat * cos(angle_ap) + c_hat * sin(angle_ap)) * R;
    return (p - a_rotated).norm() < EPS;
}