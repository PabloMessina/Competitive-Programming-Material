// Tests Geometry/2D/Point2D.cpp (with its default T = double).
// Run from the repo root (see Tests/README.md):
//   g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG Tests/test_point2d.cpp -o test.out && ./test.out
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../Geometry/2D/Point2D.cpp"

mt19937 rng(12345);
int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

// a random nonzero vector with small integer coordinates: exact in double, and lots of
// collinear vectors / vectors on the axes (the edge cases of quad() and operator<)
P rnd_vec(int c) {
    while (true) {
        P p(rnd(-c, c), rnd(-c, c));
        if (p.x != 0 || p.y != 0) return p;
    }
}

// brute-force angle in [0, 2*PI), counter-clockwise from the +x axis
double ccw_angle(const P& p) {
    double a = atan2(p.y, p.x);
    return a < 0 ? a + 2 * PI : a;
}

void test_basic_ops() {
    for (int iter = 0; iter < 10000; iter++) {
        const P a = rnd_vec(20), b = rnd_vec(20); // const: every method below must be const
        assert(a + b == P(a.x + b.x, a.y + b.y));
        assert(a - b == P(a.x - b.x, a.y - b.y));
        assert(a * 3 == P(a.x * 3, a.y * 3));
        assert((a ^ b) == a.x * b.y - a.y * b.x);
        assert((a * b) == a.x * b.x + a.y * b.y);
        assert(a.neg() == P(-a.x, -a.y));
        assert(a.rot_ccw() == P(-a.y, a.x));
        assert(a.rot_cw() == P(a.y, -a.x));
        assert(a.rot_ccw().rot_cw() == a);
        assert((a ^ a.rot_ccw()) > 0); // rot_ccw is ccw of a: cross > 0
        assert(a.norm2() == a.x * a.x + a.y * a.y);
        assert(fabs(a.norm() - hypot(a.x, a.y)) < 1e-9);
        assert(fabs(a.unit().norm() - 1) < 1e-9);
        double ang = a.angle();
        assert(-PI < ang && ang <= PI); // (-PI, PI]
        // cross product sign = orientation: b is ccw of a iff its angle is 0..180 deg ahead
        double diff = ccw_angle(b) - ccw_angle(a);
        if (diff < 0) diff += 2 * PI;
        if (fabs(diff) > 1e-9 && fabs(diff - PI) > 1e-9) assert(((a ^ b) > 0) == (diff < PI));
    }
    assert(fabs(P(-1, 0).angle() - PI) < 1e-12); // -x axis is +PI, not -PI
    puts("basic operations: OK");
}

void test_quad() {
    // axes belong to the quadrant that starts there: 0 = [0, 90], 1 = (90, 180], 2 = (180, 270), 3 = [270, 360)
    assert(P(1, 0).quad() == 0);
    assert(P(0, 1).quad() == 0);
    assert(P(-1, 0).quad() == 1);
    assert(P(0, -1).quad() == 3);
    for (int iter = 0; iter < 10000; iter++) {
        P p = rnd_vec(20);
        double a = ccw_angle(p) * 180 / PI;
        int q = p.quad();
        if (q == 0) assert(0 <= a && a <= 90 + 1e-9);
        if (q == 1) assert(90 < a && a <= 180 + 1e-9);
        if (q == 2) assert(180 < a && a < 270);
        if (q == 3) assert(270 - 1e-9 <= a && a < 360);
    }
    puts("quad: OK");
}

void test_polar_sort() {
    for (int iter = 0; iter < 2000; iter++) {
        int n = rnd(1, 40);
        vector<P> v(n);
        for (auto& p : v) p = rnd_vec(rnd(1, 10));
        sort(v.begin(), v.end());
        // sorted by angle in [0, 360), counter-clockwise from +x
        for (int i = 0; i + 1 < n; i++) assert(ccw_angle(v[i]) <= ccw_angle(v[i + 1]) + 1e-12);
        // equal under operator< exactly when same_angle, and same_angle matches the brute force
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++) {
                bool eq = !(v[i] < v[j]) && !(v[j] < v[i]);
                bool same = fabs(ccw_angle(v[i]) - ccw_angle(v[j])) < 1e-12;
                assert(eq == same);
                assert(v[i].same_angle(v[j]) == same);
            }
    }
    puts("polar sort (operator<) and same_angle: OK");
}

int main() {
    test_basic_ops();
    test_quad();
    test_polar_sort();
    puts("All Point2D tests passed");
    return 0;
}
