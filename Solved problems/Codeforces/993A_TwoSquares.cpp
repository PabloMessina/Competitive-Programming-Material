// tags: geometry, cross product
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
struct P {
    int x, y;
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator/(int d) const { return {x/d, y/d}; }
    int operator^(const P& p) const { return x*p.y - y*p.x; }
};
int turn(P &a, P &b, P &c) { return (b-a)^(c-a); }
bool in_convex_poly(P& p, vector<P>& cp) {
    int n = cp.size();
    int c0 = 0, c1 = 0;
    rep(i,0,n) {
        int t = turn(cp[i], cp[(i+1)%n], p);
        if (t <= 0) c0++;
        if (t >= 0) c1++;
    }
    return c0 == n or c1 == n;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    vector<P> a(4), b(4);
    rep(i,0,4) cin >> a[i].x >> a[i].y;
    rep(i,0,4) cin >> b[i].x >> b[i].y;
    rep(i,0,4) a[i].x *= 2, a[i].y *= 2;
    rep(i,0,4) b[i].x *= 2, b[i].y *= 2;
    bool yes = false;

    rep(i,0,4) if (in_convex_poly(a[i], b)) yes = true;
    P ac = (a[0] + a[2])/2;
    if (in_convex_poly(ac, b)) yes = true;

    rep(i,0,4) if (in_convex_poly(b[i], a)) yes = true;
    P bc = (b[0] + b[2])/2;
    if (in_convex_poly(bc, a)) yes = true;
    
    if (yes) cout << "YES\n";
    else cout << "NO\n";
    return 0;
}