// tags: greedy, priority queue, hashing
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
// A cake is three sponges of pairwise distinct sizes, and each sponge is used
// at most once. Only the frequency of each size matters.
//
// Greedy: while at least three sizes remain, take one sponge from each of the
// three currently most frequent sizes. There is always an optimal solution that
// does this, so the choice never blocks a better set of cakes. Ties are irrelevant.
//
// A max-heap holds the frequencies, so each cake costs O(log n). Scanning the
// whole frequency map once per cake would be O(n^2), too slow for n <= 2e5.
// At most n/3 cakes are built.
signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    umap<int, int> freq;
    rep(i, 0, n) {
        int a; cin >> a;
        freq[a]++;
    }
    // max-heap of the positive frequencies; the sizes themselves are no longer needed
    priority_queue<int> pq;
    for (auto& [size, count] : freq) pq.push(count);
    int cakes = 0;
    while (pq.size() >= 3) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        int c = pq.top(); pq.pop();
        // one sponge from each of these three sizes
        if (--a) pq.push(a);
        if (--b) pq.push(b);
        if (--c) pq.push(c);
        cakes++;
    }
    cout << cakes << '\n';
    return 0;
}
