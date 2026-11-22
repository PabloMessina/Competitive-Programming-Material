// Tests Data_Structures/fenwick_tree.cpp against a brute-force array.
// Run from the repo root (see Tests/README.md):
//   g++-15 -std=c++17 -O2 -Wall -Wextra -D_GLIBCXX_DEBUG Tests/test_fenwick_tree.cpp -o test.out && ./test.out
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#include "../Data_Structures/fenwick_tree.cpp"

mt19937 rng(12345);
int rnd(int a, int b) { return uniform_int_distribution<int>(a, b)(rng); }

// point update + prefix / range sum, values a[1..n]
template<typename T> void test_point_update_range_sum(T lo, T hi) {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40);
        vector<T> a(n + 1, 0);
        FT<T> ft(n);
        for (int q = 0; q < 200; q++) {
            int t = rnd(0, 2);
            if (t == 0) { // update, including the last position n
                int i = rnd(1, n);
                T v = (T)uniform_int_distribution<ll>(lo, hi)(rng);
                a[i] += v;
                ft.update(i, v);
            } else if (t == 1) { // prefix sum, including query(0) = 0
                int i = rnd(0, n);
                T s = 0;
                for (int k = 1; k <= i; k++) s += a[k];
                assert(ft.query(i) == s);
            } else { // range sum [i, j], including single positions and the whole array
                int i = rnd(1, n), j = rnd(1, n);
                if (i > j) swap(i, j);
                T s = 0;
                for (int k = i; k <= j; k++) s += a[k];
                assert(ft.query(i, j) == s);
            }
        }
    }
}

// range update + point query mode: update(i, j, v), then query(i) is the value at i
void test_range_update_point_query() {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40);
        vector<ll> a(n + 1, 0);
        FT<ll> ft(n);
        for (int q = 0; q < 200; q++) {
            if (rnd(0, 1) == 0) { // range update, including j = n (update(n + 1) must be a no-op)
                int i = rnd(1, n), j = rnd(1, n);
                if (i > j) swap(i, j);
                ll v = rnd(-50, 50);
                for (int k = i; k <= j; k++) a[k] += v;
                ft.update(i, j, v);
            } else {
                int i = rnd(1, n);
                assert(ft.query(i) == a[i]);
            }
        }
    }
    puts("range update + point query: OK");
}

// lower_bound(k): smallest i with query(i) >= k, or n + 1 if there is none
void test_lower_bound() {
    for (int iter = 0; iter < 300; iter++) {
        int n = rnd(1, 40); // includes n = 1 and sizes that aren't powers of 2
        bool counts = rnd(0, 1); // 0/1 counts (k-th element use) or general values >= 0
        vector<ll> a(n + 1, 0);
        FT<ll> ft(n);
        for (int q = 0; q < 200; q++) {
            if (rnd(0, 1) == 0) { // change a value, keeping it >= 0
                int i = rnd(1, n);
                ll v = counts ? (a[i] ? -1 : 1) : rnd(0, 5) - a[i];
                a[i] += v;
                ft.update(i, v);
            } else { // k from 1 to beyond the total (answer n + 1)
                ll total = 0;
                for (int i = 1; i <= n; i++) total += a[i];
                ll k = rnd(1, (int)total + 2);
                int exp = 0; ll s = 0; // brute force: grow the prefix until it reaches k
                while (exp < n && s < k) s += a[++exp];
                if (s < k) exp = n + 1;
                assert(ft.lower_bound(k) == exp);
                // k-th smallest element: with 0/1 counts, slot exp holds the k-th one
                if (counts && k <= total) assert(a[exp] == 1 && ft.query(exp) == k);
            }
        }
    }
    puts("lower_bound (k-th element): OK");
}

int main() {
    test_point_update_range_sum<int>(-50, 50);
    puts("point update + range sum (int): OK");
    // sums well above 2^31: needs FT<ll>
    test_point_update_range_sum<ll>(-1000000000000LL, 1000000000000LL);
    puts("point update + range sum (ll, large values): OK");
    test_range_update_point_query();
    test_lower_bound();
    puts("All fenwick tree tests passed");
    return 0;
}
