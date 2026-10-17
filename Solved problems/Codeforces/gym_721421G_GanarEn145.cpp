// tags: interactive, sqrt decomposition, blocks, linear scan
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
// Queries must go strictly right, with one reset. So: scan the block ends
// B, 2B, 3B, ... until one reaches x (at most n/B queries), reset, and scan
// the block that contains x (at most B-1 queries). With B = 60 and n <= 5000:
// 83 + 59 = 142 <= 145.
const int B = 60;

int ask(int i) {
    cout << "? " << i << endl; // endl flushes
    int a; cin >> a;
    return a;
}

void answer(int p) {
    cout << "! " << p << endl;
}

signed main() { // signed allows using #define int long long
    int n, x; cin >> n >> x;
    int lo = 1, hi = n; // x is somewhere in [lo, hi]
    bool queried = false;
    for (int i = B; i <= n; i += B) {
        int a = ask(i);
        queried = true;
        if (a == x) { answer(i); return 0; }
        if (a > x) { hi = i - 1; break; }
        lo = i + 1;
    }
    if (queried) cout << "R" << endl;
    for (int i = lo; i <= hi; i++) {
        if (ask(i) == x) { answer(i); return 0; }
    }
    return 0;
}