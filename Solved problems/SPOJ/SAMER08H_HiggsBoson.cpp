// tags: math, implementation, fractions
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
struct Fraction {
    ll a, b;
    Fraction(){}
    Fraction(ll _a, ll _b) : a(_a), b(_b) {
        if (b < 0) a = -a, b = -b;
    }
    Fraction operator*(const Fraction& o) const {
        return { a * o.a, b * o.b };
    }
    Fraction operator*(ll k) const {
        return { a * k, b };
    }
    Fraction operator+(const Fraction& o) const {
        return { a * o.b + o.a * b, b * o.b };
    }
    Fraction operator+(ll k) const {
        return { a + k * b, b };
    }
    Fraction operator-(const Fraction& o) const {
        return { (a * o.b) - (o.a * b), b * o.b };
    }
    bool operator<(const Fraction& o) const {
        return a * o.b < b * o.a;
    }
    bool operator<=(const Fraction& o) const {
        return a * o.b <= b * o.a;
    }
    bool operator==(const Fraction& o) const {
        return a * o.b == b * o.a;
    }
    void normalize() {
        ll g = __gcd(a, b);
        a /= g;
        b /= g;
        if (b < 0) a = -a, b = -b;
    }
};

Fraction ZERO = {0, 1};
void update_ans(Fraction& ans, const Fraction& t) {
    if (ZERO <= t) ans = min(ans, t);
}

ll discrete_floor(ll a, ll b) {
    return a/b - (a < 0 and a % b != 0);
}
ll discrete_ceil(ll a, ll b) {
    return a/b + (a > 0 and a % b != 0);
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    ll a1, b1, c1, d1;
    ll a2, b2, c2, d2;
    
    while (cin >> a1 >> b1 >> c1 >> d1 >> a2 >> b2 >> c2 >> d2) {
        if (not (a1 or b1 or c1 or d1 or a2 or b2 or c2 or d2)) break;

        Fraction t_min = {INT_MAX, 1};
        if (a1 == a2 and b1 == b2) {
            if (c1 == c2 and d1 == d2) {
                update_ans(t_min, {0, 1});
            } else {
                if ((a1 == 0 and b1 == 0) or (a1 != 0)) {
                    update_ans(t_min, {-b1, a1 != 0 ? a1 : 1});
                }
                if (c1 == c2) {
                    if ((d2 - d1) % 360 == 0) update_ans(t_min, ZERO);
                } else if (c1 - c2 > 0) {
                    ll k = discrete_ceil(d1 - d2, 360);
                    assert (d2 - d1 + 360 * k >= 0);
                    assert (d2 - d1 + 360 * (k-1) < 0);
                    update_ans(t_min, {d2 - d1 + 360 * k, c1 - c2});
                } else {
                    ll k = discrete_floor(d1 - d2, 360);
                    assert (d2 - d1 + 360 * k <= 0);
                    assert (d2 - d1 + 360 * (k+1) > 0);
                    update_ans(t_min, {d2 - d1 + 360 * k, c1 - c2});
                }
            }
        } else {            
            {
                Fraction t(b2 - b1, a1 - a2);
                if (t.b != 0) {
                    if (t * a1 + b1 == ZERO) update_ans(t_min, t);
                    else {
                        Fraction f = (t * c1 + d1) - (t * c2 + d2);
                        f.normalize();
                        if (f.b == 1 and (f.a % 360) == 0) update_ans(t_min, t);
                    }
                }
            }
            if (a1 == -a2 and b1 == -b2) {
                if (c1 == c2) {
                    if ((d2 - d1 + 180) % 360 == 0) update_ans(t_min, ZERO);
                } else if (c1 - c2 > 0) {
                    ll k = discrete_ceil(d1 - d2 - 180, 360);
                    assert (d2 - d1 + 180 + 360 * k >= 0);
                    assert (d2 - d1 + 180 + 360 * (k-1) < 0);
                    update_ans(t_min, {d2 - d1 + 180 + 360 * k, c1 - c2});
                } else {                    
                    ll k = discrete_floor(d1 - d2 - 180, 360);
                    assert (d2 - d1 + 180 + 360 * k <= 0);
                    assert (d2 - d1 + 180 + 360 * (k+1) > 0);
                    update_ans(t_min, {d2 - d1 + 180 + 360 * k, c1 - c2});
                }
            }
            {
                Fraction t(-b2 - b1, a1 + a2);
                if (t.b != 0) {
                    if (t * a1 + b1 == ZERO) update_ans(t_min, t);
                    else {
                        Fraction f = (t * c1 + d1) - (t * c2 + d2);
                        f.normalize();
                        if (f.b == 1 and ((f.a + 180) % 360) == 0) update_ans(t_min, t);
                    }
                }
            }
        }
        if (t_min.a == INT_MAX) {
            cout << "0 0\n";
        } else {
            t_min.normalize();
            cout << t_min.a << ' ' << t_min.b << '\n';
        }
    }
    return 0;
}