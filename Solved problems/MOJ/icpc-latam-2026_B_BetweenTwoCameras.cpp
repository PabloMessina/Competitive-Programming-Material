// tags: geometry, polar sort, cross product, counting inversions, fenwick tree
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i) // [a, b), inclusive-exclusive
#define invrep(i,b,a) for(int i = b; i >= a; --i) // [b, a], inclusive-inclusive
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
// Idea: each camera lists the cats in increasing order of angle.
//   - Camera 1 at (0,0) starts pointing at (D,0), along +x, and turns counter-clockwise: it
//     sorts the vectors (x, y) counter-clockwise.
//   - Camera 2 at (D,0) starts pointing at (0,0), along -x, and turns clockwise. Mirroring the
//     room (x -> D - x) turns it into the same picture as camera 1: it sorts the vectors
//     (D - x, y) counter-clockwise.
// Both sorts are exact with integers: the cross product decides which of two vectors comes
// first, and with coordinates up to 1e9 it is at most 1e18, which fits in a long long.
//
// A pair {A, B} is flagged when the two lists order it differently: it is an INVERSION between
// list 1 and list 2. Walk list 1 from the END to the start, and insert each cat's weight into a
// Fenwick tree at its position in list 2. When we reach cat i, the tree holds exactly the cats
// AFTER i in list 1; those at positions < pos2[i] are BEFORE i in list 2, so they form flagged
// pairs with i:
//   answer += W[i] * (sum of weights at positions [1, pos2[i] - 1])
// Each flagged pair is counted once: at whichever of its two cats comes first in list 1.
// Complexity: O(N log N).

// ---- Point2D (from Geometry/2D/Point2D.cpp, with T = long long) ----
typedef long long T; // integer coordinates: exact cross products (|cross| <= 1e18 here)
struct P { // 2D point / vector
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product: > 0 iff p is ccw of *this
    // quadrant of the direction: 0 = [0, 90] deg, 1 = (90, 180], 2 = (180, 270), 3 = [270, 360)
    int quad() const { return (x >= 0) ? (y >= 0 ? 0: 3) : (y >= 0 ? 1 : 2); }
    // polar order: counter-clockwise by angle in [0, 360) deg, starting from the +x axis.
    // Each quadrant spans less than 180 deg, so inside one quadrant the cross product decides.
    // Vectors pointing the same way compare equal. Do not sort the zero vector (0, 0).
    bool operator<(const P& p) const {
        int q = quad(), qp = p.quad();
        return q != qp ? q < qp : ((*this)^p) > 0;
    }
};

// ---- Fenwick tree (from Data_Structures/fenwick_tree.cpp, templated on the value type) ----
template<typename V> struct FT { // positions 1..n
    vector<V> t;
    FT(int n) : t(n+1, 0) {}
    V query(int i) { // sum of positions [1, i] (query(0) = 0)
        V ans = 0;
        for (; i > 0; i -= i & -i) ans += t[i];
        return ans;
    }
    V query(int i, int j) { return query(j) - query(i-1); } // sum of positions [i, j]
    void update(int i, V v) { // add v to position i
        for (; i < (int)t.size(); i += i & -i) t[i] += v;
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; ll D;
    cin >> N >> D;
    vector<P> v1(N), v2(N); // each cat as seen from camera 1 and (mirrored) from camera 2
    vector<ll> W(N);
    rep(i,0,N) {
        ll x, y; cin >> x >> y >> W[i];
        v1[i] = P(x, y);
        v2[i] = P(D - x, y);
    }
    // list 1 and list 2: cat indices in the order each camera records them.
    // The statement guarantees no ties (a camera never sees two cats at once).
    vi list1(N), list2(N);
    iota(list1.begin(), list1.end(), 0);
    iota(list2.begin(), list2.end(), 0);
    sort(list1.begin(), list1.end(), [&](int a, int b) { return v1[a] < v1[b]; });
    sort(list2.begin(), list2.end(), [&](int a, int b) { return v2[a] < v2[b]; });
    vi pos2(N); // pos2[cat] = position of the cat in list 2, 1-indexed for the Fenwick tree
    rep(k,0,N) pos2[list2[k]] = k + 1;
    // weighted inversion count. Weight sums reach 2e9 (more than an int holds) and the answer
    // reaches ~2e18 (every pair flagged, all weights 1e4): both fit in a long long
    FT<ll> ft(N);
    ll ans = 0;
    invrep(k, N-1, 0) {
        int i = list1[k];
        // cats after i in list 1 (already inserted) but before i in list 2
        ans += W[i] * ft.query(pos2[i] - 1);
        ft.update(pos2[i], W[i]);
    }
    cout << ans << '\n';
    return 0;
}
