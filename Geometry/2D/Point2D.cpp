const double PI = acos(-1);
const double EPS = 1e-12;
// use T = long long for integer inputs: cross/dot products are then exact (coords up to ~1e9).
// double rounds products above ~9e15, which can flip the sign of a cross product
typedef double T;
struct P { // 2D
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    bool operator==(const P& p) const { return x==p.x && y == p.y; } // exact, even for doubles
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    P operator/(T d) const { return {x/d, y/d}; } // truncates if T is an integer type
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product: > 0 iff p is ccw of this
    T operator*(const P& p) const { return x*p.x + y*p.y; } // dot product
    P neg() const { return { -x, -y }; }
    P rot_ccw() const { return { -y, x }; }
    P rot_cw() const { return { y, -x }; }
    T norm2() const { return x*x + y*y; } // with long long, overflows if coords > ~3e9
    double norm() const { return sqrt((double)norm2()); }
    // quadrant of the direction: 0 = [0, 90] deg, 1 = (90, 180], 2 = (180, 270), 3 = [270, 360)
    int quad() const { return (x >= 0) ? (y >= 0 ? 0: 3) : (y >= 0 ? 1 : 2); }
    double angle() const { return atan2(y, x); } // (-PI, PI]
    P unit() const { return (*this)/norm(); } // needs T = double
    // polar sort: ccw by angle in [0, 360) deg, starting at the +x axis. Each quadrant spans
    // < 180 deg, so within one the cross product decides. Same-direction vectors compare
    // equal. Don't sort the zero vector (0, 0): it breaks the strict weak ordering
    bool operator<(const P& p) const {
        int q = quad(), qp = p.quad();
        return q != qp ? q < qp : ((*this)^p) > 0;
    }
    bool same_angle(const P& p) const { // two vectors pointing to the same direction
        return quad() == p.quad() and ((*this)^p) == 0;
    }
};
