// tags: DP, top-down, memoization, interval DP, non-crossing partition, CYK, auxiliary state
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
/*
 * PROBLEM: a move deletes 3 adjacent, pairwise different characters. Can the
 * whole string be deleted?
 *
 * KEY OBSERVATION: think about which ORIGINAL positions i < k < m get deleted
 * together in each move. When they are deleted they are adjacent, so everything
 * originally between them was deleted before. Hence two triples can never
 * interleave: they are either nested or side by side (a non-crossing partition
 * into triples), and moves in different branches don't interfere. So the
 * question becomes: can the string be partitioned into non-crossing triples of
 * distinct letters? This is a question about segments -> interval DP.
 *
 * DP (segments are inclusive, s[l..r]; an empty segment, l > r, is erasable):
 *
 *   can(l, r)    = can s[l..r] be completely erased on its own?
 *                  Look at the triple containing the leftmost character s[l],
 *                  and say it ends at position m. Then s[l..m] is erased
 *                  "as a block" and the rest s[m+1..r] must be erasable:
 *                    can(l, r) = OR over m: closed(l, m) AND can(m+1, r)
 *
 *   closed(l, m) = can s[l..m] be erased with s[l] and s[m] in the SAME triple?
 *                  The middle character of the triple is some s[k], and the two
 *                  gaps inside the triple must be erased first, independently:
 *                    closed(l, m) = OR over k: {s[l], s[k], s[m]} distinct
 *                                   AND can(l+1, k-1) AND can(k+1, m-1)
 *
 * Choosing k and m in a single transition would cost O(N^2) per segment, O(N^4)
 * total. The auxiliary function closed() splits that choice into two steps of
 * O(N) each, so the total is O(N^3). (Same idea as binarizing a grammar for
 * CYK: S -> empty | C S,  C -> x S y S z.)
 *
 * Only segments whose length is a multiple of 3 can be erased, so m and k move
 * in steps of 3. That leaves ~N^3/54 checks per function, ~2e7 for N = 999.
 */

const int MAXN = 1000;
string s;
int n;
// memo: -1 = not computed yet, 0 = false, 1 = true
signed char memo_can[MAXN][MAXN], memo_closed[MAXN][MAXN];

bool closed(int l, int m);

bool can(int l, int r) {
    if (l > r) return true;                  // empty segment
    if ((r - l + 1) % 3 != 0) return false;  // lengths must be multiples of 3
    signed char& ans = memo_can[l][r];
    if (ans != -1) return ans;
    // s[l]'s triple ends at m: s[l..m] must have length multiple of 3
    for (int m = l + 2; m <= r; m += 3) {
        if (closed(l, m) && can(m + 1, r)) return (ans = 1);
    }
    return (ans = 0);
}

bool closed(int l, int m) {
    // here (m - l + 1) % 3 == 0 always holds (guaranteed by the caller)
    signed char& ans = memo_closed[l][m];
    if (ans != -1) return ans;
    // the gap s[l+1..k-1] must have length multiple of 3 -> k = l+1, l+4, ...
    // (then the gap s[k+1..m-1] automatically also has length multiple of 3)
    for (int k = l + 1; k < m; k += 3) {
        if (s[l] != s[k] && s[k] != s[m] && s[l] != s[m]
            && can(l + 1, k - 1) && can(k + 1, m - 1)) return (ans = 1);
    }
    return (ans = 0);
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> s;
    n = s.size();
    memset(memo_can, -1, sizeof memo_can);
    memset(memo_closed, -1, sizeof memo_closed);
    cout << (can(0, n - 1) ? 'S' : 'N') << '\n';
    return 0;
}
