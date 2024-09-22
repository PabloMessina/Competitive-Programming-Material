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
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------

const int MAXN = 25000 + 5;
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
    T norm2() { return x*x + y*y; }    
};

// Line - Line Intersection
// return whether straight lines <-a-b-> and <-c-d-> intersect each other at a specific point
// if they do, we assign values to t1 and t2 such that
//    a + (b - a) * t1 == c + (d - c) * t2
bool intersect_lines(const P& a, const P& b, const P& c, const P& d, double& t1, double& t2) {
    P c_d = c-d;
    P b_a = b-a;
    double x = b_a^c_d;
    if (abs(x) < EPS) return false; // parallel
    P c_a = c-a;
    t1 = c_a^c_d/x;
    t2 = b_a^c_a/x;
    return true;
}

T turn(const P &a, const P &b, const P &c) { return (b-a)^(c-a); }

bool on_line(const P& a, const P& b, const P& p) { return abs(turn(a,b,p)) < EPS; }

int n;
int S[MAXN];
P A[MAXN], B[MAXN], D[MAXN]; // A = initial position, D = direction, B = A + D

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // Read input
    cin >> n;
    rep(i,0,n) {
        int x, y, dx, dy, s;
        cin >> x >> y >> dx >> dy >> s;
        A[i] = P(x, y);
        D[i] = P(dx, dy);
        B[i] = A[i] + D[i];
        S[i] = s;
    }
    // For each pair of points, calculate the minimum time for them to collide (if they do)
    double ans = 1e20;
    rep(i,0,n) {
        rep(j,i+1,n) {
            double ti, tj;
            // Case 1: if lines intersect at a single point
            if (intersect_lines(A[i], B[i], A[j], B[j], ti, tj)) {
                if (ti < 0 or tj < 0) continue; // collision in the past
                P col_p = A[i] + D[i] * ti; // collision point
                double di = (col_p - A[i]).norm2();
                ti = (di / S[i]) / S[i]; // time to reach collision (square of time)
                double dj = (col_p - A[j]).norm2();
                tj = (dj / S[j]) / S[j]; // time to reach collision (square of time)
                ans = min(ans, max(ti, tj));
            // Case 2: if lines are the same and each car is facing the other
            } else if (on_line(A[i], B[i], A[j]) and on_line(A[j], B[j], A[i]) and
                      (B[i] - A[i]) * (A[j] - A[i]) >= 0 and (B[j] - A[j]) * (A[i] - A[j]) >= 0) {
                double s = S[i] + S[j];
                ans = min(ans, (A[i] - A[j]).norm2() / s / s);
            // Case 3.1: if car i is moving towards car j
            } else if (on_line(A[i], B[i], A[j]) and (B[i] - A[i]) * (A[j] - A[i]) >= 0) {
                double s = S[i];
                ans = min(ans, (A[i] - A[j]).norm2() / s / s);
            // Case 3.2: if car j is moving towards car i
            } else if (on_line(A[j], B[j], A[i]) and (B[j] - A[j]) * (A[i] - A[j]) >= 0) {
                double s = S[j];
                ans = min(ans, (A[i] - A[j]).norm2() / s / s);
            }
        }
    }
    if (ans == 1e20) {
        cout << "No show :(\n";
    } else {
        cout << setprecision(20) << sqrt(ans) << "\n"; // square root of time
    }
    return 0;
}