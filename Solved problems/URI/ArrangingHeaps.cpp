// tags: DP, Convex Hull Trick
// reference: https://wcipeg.com/wiki/Convex_hull_trick
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// -------------------------------
const int MAXN = 1000;
int N,K;
ll X[MAXN];
ll Wacc[MAXN], XWacc[MAXN]; // accumulated sums
ll DP[MAXN][MAXN];

// Fraction: numerator / denominator
struct Fraction {
    ll num, den;
    bool operator<(const Fraction& o) const {
        return num * o.den < o.num * den;
    }
    bool operator<=(const Fraction& o) const {
        return num * o.den <= o.num * den;
    }
    bool operator==(const Fraction& o) const {
        return num * o.den == o.num * den;
    }
};

// Line: slope (m), intercept(b) and domain [x_left, x_right]
struct Line {
    ll m, b;
    Fraction x_left, x_right; // we use fractions to avoid float point precision errors
};
// stack of lines, used to keep track of the lower envelope of multiple
// line equations
Line lines_stack[MAXN]; 
int stack_size; // current size of the stack

// Add a new line defined by (m=slope, b=intercept) to the lines_stack
// satisfying the invariant that all lines in the stack belong to the
// lower envelope. This implies iteratively removing lines from the top of
// the stack if they become hidden by the new line being added.
void addline(ll m, ll b) {
    if (stack_size == 0) {
        Line& newl = lines_stack[0];
        newl.m = m;
        newl.b = b;
        newl.x_left = {LLONG_MIN,1};
        newl.x_right = {LLONG_MAX,1};
    } else {
        while (stack_size > 1) {
            Line& prevl1 = lines_stack[stack_size-1];
            Line& prevl2 = lines_stack[stack_size-2];
            // x-coordinates of intersections
            //  x1: intersection between prevl1 and prevl2
            Fraction x1 = { prevl2.b - prevl1.b, prevl1.m - prevl2.m };
            //  x2: intersection between prevl2 and new line
            Fraction x2 = { prevl2.b - b, m - prevl2.m };
            // if line at the top of the stack gets hidden by new line
            // -> remove it
            if (x1 <= x2) stack_size--; 
            else break;
        }
        Line& prevl = lines_stack[stack_size-1];
        Fraction x = {prevl.b - b, m - prevl.m};
        Line& newl = lines_stack[stack_size];
        newl.m = m;
        newl.b = b;
        newl.x_left = {LLONG_MIN,1};
        newl.x_right = x;
        prevl.x_left = x;
    }
    stack_size++;
}

// Find with binary search the correct line in the lines_stack
// whose domain contains x, and return the line equation evaluated
// at x.
ll lower_envelope_eval(ll x) {
    Fraction f = {x, 1};
    int i = 0, j = stack_size-1;
    while (i < j) {
        int m = (i+j)>>1;
        if (lines_stack[m].x_left <= f) {
            j = m;
        } else {
            i = m+1;
        }
    }
    Line& l = lines_stack[i];
    return l.m * x + l.b;
}

// cost of moving all heaps in range [i, j] to j
ll cost(int i, int j) {
    if (i > 0) return X[j] * (Wacc[j] - Wacc[i-1]) - (XWacc[j] - XWacc[i-1]);
    return X[j] * Wacc[j] - XWacc[j];
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while(cin >> N >> K) {
        ll accw = 0, accxw = 0;
        rep(i,0,N) {
            ll x, w; cin >> x >> w;
            X[i] = x;
            accw = Wacc[i] = accw + w;
            accxw = XWacc[i] = accxw + x * w;
        }
        // base case of DP: k = 1
        rep(i,0,N) DP[i][1] = cost(i, N-1);
        // general cases
        rep(k,2,K+1) {
            stack_size = 0; // reset stack
            invrep(i,N-k,0) {
                // slope and intercept
                ll m = -X[i];
                ll b = X[i] * Wacc[i] - XWacc[i] + DP[i+1][k-1];
                addline(m, b);
                // find minimum value with binsearch over lower envelope
                // of lines
                DP[i][k] = i > 0 ?
                    lower_envelope_eval(Wacc[i-1]) + XWacc[i-1] :
                    lower_envelope_eval(0);
            }
        }
        cout << DP[0][K] << '\n';
    }
    return 0;
}