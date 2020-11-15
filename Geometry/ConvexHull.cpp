#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
typedef long long int ll;
// ----------------------------------------------
// Convex Hull: Andrew's Montone Chain Algorithm 
// ----------------------------------------------
struct Point {
    ll x, y;
    ll operator^(const Point<ll>& p) const { return x*p.y - y*p.x; }
    bool operator<(const Point& p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
ll turn(Point& a, Point& b, Point& c) { return (b-a)^(c-a); }

vector<Point> upper_hull(vector<Point>& P) {
    // sort points lexicographically
    int n = P.size(), k = 0;
    sort(P.begin(), P.end());
    // build upper hull
    vector<Point> uh(n);
    invrep (i, n-1, 0) {
        while (k >= 2 && turn(uh[k-2], uh[k-1], P[i]) <= 0) k--;
        uh[k++] = P[i];
    }
    uh.resize(k);
    return uh;
}

vector<Point> lower_hull(vector<Point>& P) {
    // sort points lexicographically
    int n = P.size(), k = 0;
    sort(P.begin(), P.end());
    // collect lower hull
    vector<Point> lh(n);
    rep (i, 0, n-1) {
        while (k >= 2 && turn(lh[k-2], lh[k-1], P[i]) <= 0) k--;
        lh[k++] = P[i];
    }
    lh.resize(k);
    return lh;
}

vector<Point> convex_hull(vector<Point>& P) {
    int n = P.size(), k = 0;
    // set initial capacity
    vector<Point> H(2*n);
    // sort points lexicographically
    sort(P.begin(), P.end());
    // build lower hull
    for (int i = 0; i < n; ++i) {
        while (k >= 2 && turn(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // build upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && turn(H[k-2], H[k-1], P[i]) <= 0) k--;
        H[k++] = P[i];
    }
    // remove extra space
    H.resize(k-1);
    return H;
}