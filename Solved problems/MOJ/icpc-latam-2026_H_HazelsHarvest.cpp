// tags: offline queries, sweep, k-th smallest, fenwick tree, binary lifting, binary search
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
// Idea: for an order (K, V), tree i counts from year
//   r_i = max(Y_i, Y_i + V - H_i)   (planted, and tall enough)
// and forever after, so the answer is the K-th smallest r_i. Two groups:
//   - group A, H_i >= V (tall when planted): r_i = Y_i
//   - group B, H_i <  V (has to grow):       r_i = c_i + V, with c_i = Y_i - H_i
// Process the orders by increasing V (offline): each tree starts in A and moves to B exactly
// once, when V passes H_i. Each group is a Fenwick tree of 0/1 counts over its trees sorted
// (by Y for A, by c for B), so lower_bound(j) finds the j-th smallest of a group in O(log N).
//
// K-th smallest of A u B: take x from A and K - x from B,
//   answer = min over x of max(A_x, B_{K-x}),   A_0 = B_0 = -INF.
// A_x goes up with x and B_{K-x} goes down, so binary search the first x with
// A_x >= B_{K-x}; the minimum is at that x or at x - 1. (Not ternary search: repeated values
// make flat stretches that ternary search can't handle.)
// Complexity: O((N + Q) log^2 N).

// ---- Fenwick tree (from Data_Structures/fenwick_tree.cpp) ----
template<typename T> struct FT { // fenwick tree, 1-indexed: positions 1..n
    vector<T> t;
    FT(int n) : t(n+1, 0) {}
    void update(int i, T v) { // increment i'th value by v (and propagate)
        for (; i < (int)t.size(); i += (i & -i)) t[i] += v;
    }
    // smallest i with query(i) >= k (k >= 1), or n+1 if query(n) < k. O(log n).
    // With 0/1 counts, this is the slot of the k-th smallest element.
    int lower_bound(T k) {
        int n = (int)t.size() - 1, pos = 0;
        for (int pw = 1 << __lg(max(n, 1)); pw > 0; pw >>= 1)
            if (pos + pw <= n && t[pos + pw] < k) { pos += pw; k -= t[pos]; }
        return pos + 1;
    }
};

const ll NEG_INF = LLONG_MIN; // "take nothing from this group": only compared, never added to

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int N; cin >> N;
    vector<ll> Y(N), H(N), C(N);
    rep(i,0,N) {
        cin >> Y[i] >> H[i];
        C[i] = Y[i] - H[i]; // r_i = C[i] + V once the tree is in group B (can be negative)
    }
    // the trees sorted by Y (slots of Fenwick tree A), by C (slots of B) and by H (sweep order)
    vi byY(N), byC(N), byH(N);
    iota(byY.begin(), byY.end(), 0);
    iota(byC.begin(), byC.end(), 0);
    iota(byH.begin(), byH.end(), 0);
    sort(byY.begin(), byY.end(), [&](int a, int b) { return Y[a] < Y[b]; });
    sort(byC.begin(), byC.end(), [&](int a, int b) { return C[a] < C[b]; });
    sort(byH.begin(), byH.end(), [&](int a, int b) { return H[a] < H[b]; });
    vi slotY(N), slotC(N); // 1-indexed slot of each tree in each Fenwick tree
    rep(k,0,N) {
        slotY[byY[k]] = k + 1;
        slotC[byC[k]] = k + 1;
    }
    FT<int> ftA(N), ftB(N); // ftA: 1 if the tree is in group A; ftB: 1 if it is in group B
    rep(k,1,N+1) ftA.update(k, 1); // every tree starts in group A
    int sizeA = N, sizeB = 0;

    int Q; cin >> Q;
    vector<ll> K(Q), V(Q), ans(Q);
    rep(q,0,Q) cin >> K[q] >> V[q];
    vi byV(Q); // answer the orders by increasing V (offline), storing each at its index
    iota(byV.begin(), byV.end(), 0);
    sort(byV.begin(), byV.end(), [&](int a, int b) { return V[a] < V[b]; });

    int next = 0; // next tree (in byH order) still in group A
    for (int q : byV) {
        ll v = V[q];
        int k = K[q];
        // trees with H < v are no longer tall enough when planted: move them from A to B.
        // (H == v could go either way: then c + v = Y - H + v = Y, the same year in both groups)
        while (next < N && H[byH[next]] < v) {
            int i = byH[next++];
            ftA.update(slotY[i], -1); sizeA--;
            ftB.update(slotC[i], +1); sizeB++;
        }
        // x-th smallest r of group A, and y-th smallest r of group B
        auto a_kth = [&](int x) { return x == 0 ? NEG_INF : Y[byY[ftA.lower_bound(x) - 1]]; };
        auto b_kth = [&](int y) { return y == 0 ? NEG_INF : C[byC[ftB.lower_bound(y) - 1]] + v; };
        // take x from A and k - x from B: needs x <= sizeA and k - x <= sizeB
        int lo = max(0, k - sizeB), hi = min(k, sizeA);
        // first x in [lo, hi] with a_kth(x) >= b_kth(k - x), or hi + 1 if there is none
        int L = lo, R = hi + 1;
        while (L < R) {
            int x = (L + R) / 2;
            if (a_kth(x) >= b_kth(k - x)) R = x;
            else L = x + 1;
        }
        // the minimum of max(a_kth(x), b_kth(k - x)) is right at the crossing or just before it
        ll best = LLONG_MAX;
        for (int x : {L - 1, L})
            if (lo <= x && x <= hi)
                best = min(best, max(a_kth(x), b_kth(k - x)));
        ans[q] = best;
    }
    rep(q,0,Q) cout << ans[q] << '\n';
    return 0;
}
