// Tests Data_Structures/segment_tree_lazy.cpp against a brute-force array.
// Run from the repo root (see Tests/README.md):
//   g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG Tests/test_segment_tree_lazy.cpp -o test.out && ./test.out
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
// the template has its own main() with examples; rename it so it doesn't clash
#define main example_main
#include "../Data_Structures/segment_tree_lazy.cpp"
#undef main

mt19937 rng(12345);
int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

void test_add_sum() {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        vector<SumNode> init(n);
        for (int i = 0; i < n; i++) a[i] = rnd(0, 50), init[i] = {a[i], 1};
        RangeAddSum st(init);
        for (int q = 0; q < 200; q++) {
            int t = rnd(0, 5);
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            if (t == 0) { // range add (non-negative so prefix sums are monotone)
                ll v = rnd(0, 20);
                for (int i = l; i < r; i++) a[i] += v;
                st.apply(l, r, v);
            } else if (t == 1) { // range sum
                ll s = 0;
                for (int i = l; i < r; i++) s += a[i];
                assert(st.prod(l, r).sum == s);
            } else if (t == 2) { // point set / get
                int p = rnd(0, n - 1);
                a[p] = rnd(0, 50);
                st.set(p, {a[p], 1});
                assert(st.get(rnd(0, n - 1)).len == 1);
                int p2 = rnd(0, n - 1);
                assert(st.get(p2).sum == a[p2]);
            } else if (t == 3) { // max_right: largest r2 with sum(a[l..r2)) <= T
                ll T = rnd(0, 500);
                int exp = l; ll s = 0;
                while (exp < n && s + a[exp] <= T) s += a[exp++];
                assert(st.max_right(l, [&](SumNode x) { return x.sum <= T; }) == exp);
            } else if (t == 4) { // min_left: smallest l2 with sum(a[l2..r)) <= T
                ll T = rnd(0, 500);
                int exp = r; ll s = 0;
                while (exp > 0 && s + a[exp - 1] <= T) s += a[--exp];
                assert(st.min_left(r, [&](SumNode x) { return x.sum <= T; }) == exp);
            } else { // all_prod
                assert(st.all_prod().sum == accumulate(a.begin(), a.end(), 0LL));
            }
        }
    }
    puts("range add + sum: OK");
}

void test_assign_min() {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-50, 50);
        RangeAssignMin st(a);
        for (int q = 0; q < 200; q++) {
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            if (rnd(0, 1)) {
                ll v = rnd(-50, 50);
                for (int i = l; i < r; i++) a[i] = v;
                st.apply(l, r, v);
            } else {
                ll m = LLONG_MAX;
                for (int i = l; i < r; i++) m = min(m, a[i]);
                assert(st.prod(l, r) == m);
            }
        }
    }
    puts("range assign + min: OK");
}

int main() {
    test_add_sum();
    test_assign_min();
    puts("--- example main output ---");
    example_main();
}
