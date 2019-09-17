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