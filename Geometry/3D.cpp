const double EPS = 1e-9;
typedef double T;
struct P { // 3D
    T x, y, z;
    friend istream& operator >> (istream& in, P& p) { return in >> p.x >> p.y >> p.z; }
    bool operator==(const P& p) const { return x==p.x and y==p.y and z==p.z; }
    P operator+(const P& p) const { return {x+p.x, y+p.y, z+p.z}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y, z-p.z}; }
    P operator*(T d) const { return {x*d, y*d, z*d}; }
    P operator/(T d) const { return {x/d, y/d, z/d}; }
    P operator^(const P& p) const { return { y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y*p.x }; }
    T operator*(const P& p) const { return x*p.x + y*p.y + z*p.z; }
    T norm2() { return x*x + y*y + z*z; }
    double norm() { return sqrt(norm2()); }
    P unit() { return (*this)/norm(); }
    static P from_sphere_coords(T r, T u, T v) {
        return { r*cos(u)*cos(v), r*cos(u)*sin(v), r*sin(u) };
    }
};
// compute angle (0 <= angle <= PI) between vectors a and b
// ** for better performance, the norms can be precomputed
//   or norms can be ommited altogether if a and b are unit vectors
double angle_between(P& a, P& b) {
    return acos(a*b/(a.norm()*b.norm()));
}
// check if point p belongs to the sphere arc from a to b.
// ** this assumes that a and b are points on a sphere centered at (0,0,0),
// and the sphere arc from a to b is the shortest path on the sphere connecting them
bool point_in_arc(P& a, P& b, P& p) {
    double angle_ab = angle_between(a, b);
    double angle_ap = angle_between(a, p);    
    if (angle_ap > angle_ab) return false;
    P n = a^b;
    P c_hat = (n^a).unit();
    double R = a.norm();
    P a_hat = a * (1./R);
    P a_rotated = (a_hat * cos(angle_ap) + c_hat * sin(angle_ap)) * R;
    return (p - a_rotated).norm() < EPS;
}

// Projecting points into a plane
struct Plane {
    double a, b, c, d; // ax + by + cz = d
    P p0, n; // p0 = point in plane, n = normal vector
    void compute_normal() {
        P p1, p2;
        if (abs(a) > EPS) {
            p0 = { d/a, 0, 0 };
            p1 = { (d-b)/a, 1, 0 };
            p2 = { (d-c)/a , 0, 1 };
        } else if (abs(b) > EPS) {
            p0 = { 0, d/b, 0 };
            p1 = { 1, (d-a)/b, 0 };
            p2 = { 0, (d-c)/b, 1 };
        } else {
            p0 = {0, 0, d/c};
            p1 = {0, 1, (d-b)/c};
            p2 = {1, 0, (d-a)/c};
        }
        n = ((p1-p0)^(p2-p0)).unit();
    }
    Plane (double a, double b, double c, double d) : a(a), b(b), c(c), d(d) {
        compute_normal();
    }
    P project(const P& p) { return p - n*(n*(p-p0)); }
};