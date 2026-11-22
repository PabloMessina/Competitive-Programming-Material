// Tests Data_Structures/segment_tree.cpp (iterative ST and recursive STRec) against a brute-force array.
// Run from the repo root (see Tests/README.md):
//   g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG Tests/test_segment_tree.cpp -o test.out && ./test.out
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// the template has its own main() with examples; rename it so it doesn't clash
#define main example_main
#include "../Data_Structures/segment_tree.cpp"
#undef main

mt19937 rng(12345);
int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

// sum node with long long values
struct rsumq {
    ll value;
    rsumq() { value = 0; }
    rsumq(ll x) { value = x; }
    rsumq(const rsumq &a, const rsumq &b) { value = a.value + b.value; }
};

// NON-commutative node (string concatenation): checks that query() combines left to right
struct concat {
    string s;
    concat() {}
    concat(char c) { s = string(1, c); }
    concat(const concat &a, const concat &b) { s = a.s + b.s; }
};

// iterative ST: random set_point / query(l, r) on [l, r), compared with a brute force.
// `make` builds a random leaf value, `check` compares a node with the brute-force answer
template<class node, class V, class Make, class Check>
void test_iterative(Make make, Check check) {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40); // includes n = 1 and sizes that aren't powers of 2
        vector<V> a(n);
        vector<node> init(n);
        for (int i = 0; i < n; i++) a[i] = make(), init[i] = node(a[i]);
        ST<node> st(init);
        for (int q = 0; q < 200; q++) {
            if (rnd(0, 1) == 0) { // point set
                int p = rnd(0, n - 1);
                a[p] = make();
                st.set_point(p, node(a[p]));
            } else { // query [l, r), including empty ranges (l == r) and the whole array
                int l = rnd(0, n), r = rnd(0, n);
                if (l > r) swap(l, r);
                assert(check(st.query(l, r), a, l, r));
            }
        }
    }
}

// recursive STRec<t>: random update (add) / query(a, b) on [a, b] inclusive
template<class t> void test_recursive(function<ll(ll, ll)> op, ll neutral) {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-50, 50);
        STRec<t> st(a);
        for (int q = 0; q < 200; q++) {
            if (rnd(0, 1) == 0) { // add to one position
                int p = rnd(0, n - 1);
                ll v = rnd(-50, 50);
                a[p] += v;
                st.update(p, v);
            } else { // inclusive query [l, r]
                int l = rnd(0, n - 1), r = rnd(0, n - 1);
                if (l > r) swap(l, r);
                ll exp = neutral;
                for (int i = l; i <= r; i++) exp = op(exp, a[i]);
                assert(st.query(l, r) == exp);
            }
        }
    }
}

int main() {
    // iterative: sum with values far beyond 2^31
    test_iterative<rsumq, ll>(
        [] { return (ll)rnd(-1000000000, 1000000000) * rnd(1, 1000); },
        [](const rsumq& x, const vector<ll>& a, int l, int r) {
            ll s = 0;
            for (int i = l; i < r; i++) s += a[i];
            return x.value == s;
        });
    puts("iterative ST, range sum: OK");
    // iterative: min with small values (lots of ties); an empty range gives the neutral INT_MAX
    test_iterative<rminq, int>(
        [] { return rnd(-5, 5); },
        [](const rminq& x, const vector<int>& a, int l, int r) {
            int m = INT_MAX;
            for (int i = l; i < r; i++) m = min(m, a[i]);
            return x.value == m;
        });
    puts("iterative ST, range min (rminq): OK");
    // iterative: non-commutative operation, so the order of ansl / ansr matters
    test_iterative<concat, char>(
        [] { return (char)('a' + rnd(0, 25)); },
        [](const concat& x, const vector<char>& a, int l, int r) {
            return x.s == string(a.begin() + l, a.begin() + r);
        });
    puts("iterative ST, non-commutative (concatenation): OK");

    test_recursive<RSQ>([](ll x, ll y) { return x + y; }, 0);
    puts("recursive STRec, range sum (RSQ): OK");
    test_recursive<RMinQ>([](ll x, ll y) { return min(x, y); }, LLONG_MAX);
    puts("recursive STRec, range min (RMinQ): OK");
    test_recursive<RMaxQ>([](ll x, ll y) { return max(x, y); }, LLONG_MIN);
    puts("recursive STRec, range max (RMaxQ): OK");

    puts("--- example main output (expected 17 and 149) ---");
    example_main();
    return 0;
}
