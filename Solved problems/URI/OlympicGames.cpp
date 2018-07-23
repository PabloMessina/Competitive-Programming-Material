// tags: point-line duality, convex hull, two pointers, geometry
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
// -------------------------------

const int MAXN = 100000;
int N;
struct Range { double a, b; int index; };
struct Point {
    ll x, y; int index;
    bool operator<(const Point& rhs) { // custom < for lexicographic sort
        if (x == rhs.x) return y < rhs.y;
        return x < rhs.x;
    }
    bool operator==(const Point& rhs) {
        return x==rhs.x && y==rhs.y;
    }
};
Point H[MAXN], C[MAXN]; // H: ability, C: tiredness

// returns the cross product (b - a) x (c - a) which can be used to know
// if point c is to the left (> 0), collinear (== 0) or to the right (< 0)
// of the ray (a -> b)
ll cross(Point& a, Point& b, Point& c) {
    ll dx0 = b.x - a.x, dy0 = b.y - a.y;
    ll dx1 = c.x - a.x, dy1 = c.y - a.y;
    return dx0 * dy1 - dx1 * dy0;
}

// returns the indexes of the points in the lower hull, using
// Andrew's Montone Chain Algorithm
vector<int> get_lower_hull(Point* pts) {
    static int idxs[MAXN];
    // sort points lexicographically
    auto cmp = [&pts](int i, int j) { return pts[i] < pts[j]; };
    rep(i,0,N-1) idxs[i] = i;
    sort(idxs, idxs+N, cmp);
    // build lower hull
    vector<int> lh(N);
    int k = 0;
    rep(i,0,N-1) {
        int j = idxs[i];
        while (k >= 2 and cross(pts[lh[k-2]], pts[lh[k-1]], pts[j]) <= 0) k--;
        lh[k++] = j;
    }
    if (k >= 2 and pts[lh[k-2]].x == pts[lh[k-1]].x) k--;
    lh.resize(k);
    return lh;
}

// Returns a list of ranges defining a partition of the x-axis, in which
// each range is a tuple (left, right, index), meaning that the athlete 'index'
// is the best one during time interval [left, right]. The limit between ranges
// are obtained by recovering the primal lines from the dual points of the lower
// hull and solving a straightforward line intersection equation.
vector<Range> get_ranges(Point* pts, vector<int>& lh) {
    int n = lh.size();
    vector<Range> ranges(n);
    double start = INT_MIN;
    rep(i,0,n-2) {
        int j1 = lh[i];
        int j2 = lh[i+1];
        Point& p1 = pts[j1];
        Point& p2 = pts[j2];
        ll m1 = p1.x, n1 = -p1.y;
        ll m2 = p2.x, n2 = -p2.y;
        double x_int = (n1 - n2) / (double)(m2 - m1);
        ranges[i] = {start, x_int, j1};
        start = x_int;
    }
    ranges[n-1] = {start, (double)INT_MAX, lh[n-1]}; // last range
    return ranges;
}

// Given the upper envelope x-ranges for ability (h) and tiredeness (c),
// counts the number of golden athletes using 2 pointers.
int count_golden(vector<Range>& h_ranges, vector<Range>& c_ranges) {
    int n = h_ranges.size(), m = c_ranges.size();
    int i = 0, j = 0;
    int count = 0;
    while (i < n and j < m) {
        Range& ri = h_ranges[i];
        Range& rj = c_ranges[j];
        double a = max(ri.a, rj.a);
        double b = min(ri.b, rj.b);
        if (0 < b and a < b and ri.index == rj.index) count++;
        if (b == ri.b) i++;
        if (b == rj.b) j++;
    }
    return count;
}

int main() {
    scanf("%d", &N);
    rep(i,0,N-1) { // read input
        ll hn, hm, cn, cm; scanf("%lld%lld%lld%lld",&hn, &hm, &cn, &cm);
        H[i] = {hm, -hn, i};
        C[i] = {-cm, cn, i};
    }
    vector<int> h_lh = get_lower_hull(H);
    vector<int> c_lh = get_lower_hull(C);
    vector<Range> h_ranges = get_ranges(H, h_lh);
    vector<Range> c_ranges = get_ranges(C, c_lh);
    printf("%d\n", count_golden(h_ranges, c_ranges));
    return 0;
}