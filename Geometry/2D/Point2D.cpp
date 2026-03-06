const double PI = acos(-1);
const double EPS = 1e-12;
typedef double T;
struct P { // 2D
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    bool operator==(const P& p) const { return x==p.x && y == p.y; }
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    P operator/(T d) const { return {x/d, y/d}; }
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product
    T operator*(const P& p) const { return x*p.x + y*p.y; } // dot product
    P neg() { return { -x, -y }; }
    P rot_ccw() { return { -y, x }; }
    P rot_cw() { return { y, -x }; }
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
    int quad() const { return (x >= 0) ? (y >= 0 ? 0: 3) : (y >= 0 ? 1 : 2); } // 0, 1, 2, 3        
    double angle() { return atan2(y, x); } // [-PI, PI] 
    P unit() { return (*this)/norm(); }
    bool operator<(const P& p) const { // smaller quadrant or same quadrant and to the right
        int q = quad(), qp = p.quad();
        return q != qp ? q < qp : ((*this)^p) > 0;
    }
    bool same_angle(const P& p) { // two vectors pointing to the same direction
        return quad() == p.quad() and ((*this)^p) == 0;
    }
};