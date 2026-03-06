template<typename T> struct Fraction {
    T x, y; // x / y
    Fraction() : x(0), y(1) {}
    Fraction(T x_, T y_) : x(x_), y(y_) { if (y < 0) x = -x, y = -y; simplify(); }
    bool operator<(const Fraction& o) const { return x * o.y < y * o.x; }
    bool operator==(const Fraction& o) const { return x * o.y == y * o.x; }
    bool operator<=(const Fraction& o) const { return x * o.y <= y * o.x;}
    Fraction operator+(const Fraction& o) const {
        Fraction ans = {x * o.y + y * o.x, y * o.y}; ans.simplify(); return ans;
    }
    Fraction operator-(const Fraction& o) const {
        Fraction ans = {x * o.y - y * o.x, y * o.y}; ans.simplify(); return ans;
    }
    Fraction operator*(const Fraction& o) const {
        Fraction ans = {x * o.x, y * o.y}; ans.simplify(); return ans;
    }
    void simplify() {
        T g = __gcd(x, y); x /= g; y /= g;
    }
};