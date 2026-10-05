// tags: math, number theory, repunits, digit sum, big numbers, modular arithmetics
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
 * PROBLEM: minimum number of banknotes 1, 11, 111, ... (repunits) that sum to X,
 * where X has up to 100001 digits.
 *
 * KEY TRICK: multiply by 9. The repunit with k ones is R_k = (10^k - 1) / 9.
 * If we use c_k notes of R_k and S = sum c_k notes in total, then
 *     X = sum c_k (10^k - 1) / 9   <=>   9X + S = sum_{k>=1} c_k * 10^k
 * So we need to write N = 9X + S as a sum of powers of ten 10^1, 10^2, ...
 * using EXACTLY S of them.
 *
 * WHEN IS THAT POSSIBLE?
 *   - There is no 10^0 term (every note has at least one 1), so N must end in 0.
 *   - The fewest powers of ten summing to N is digitsum(N) (use the decimal
 *     digits as the c_k), so we need digitsum(N) <= S.
 *   - We can use MORE: replacing one 10^k by ten 10^(k-1) adds exactly 9 notes.
 *     And S - digitsum(N) is always a multiple of 9, because
 *     digitsum(N) = N = 9X + S = S (mod 9). So splits land exactly on S.
 *     (Splitting can go on until everything is 10^1, i.e. N/10 notes, and
 *     S <= N/10 <=> S <= X, which holds: X notes of 1 always work.)
 *   So:  S is achievable  <=>  N % 10 == 0  and  digitsum(N) <= S.
 *
 * ALGORITHM: try S = 1, 2, 3, ... and output the first S that works.
 * The answer is small: digitsum(N) <= 9 * (number of digits of N) < 10^6 - 10,
 * and within any 10 consecutive values of S one makes N end in 0. So S < 10^6, and adding
 * S to 9X only changes the LAST 7 DIGITS of 9X, plus possibly a carry of 1
 * into the rest. Split 9X = H * 10^7 + lo, precompute digitsum(H) and
 * digitsum(H + 1), and each candidate S is checked in O(7).
 */

const int LOW_DIGITS = 7;
const int LOW_MOD = 10000000; // 10^LOW_DIGITS

int digitsum(int x) {
    int s = 0;
    while (x > 0) { s += x % 10; x /= 10; }
    return s;
}

signed main() { // signed allows using #define int long long
    ios::sync_with_stdio(false); cin.tie(0);
    string x; cin >> x;

    // nine_x = digits of 9X, least significant digit first
    vi nine_x;
    int carry = 0;
    invrep(i, (int)x.size() - 1, 0) {
        int v = (x[i] - '0') * 9 + carry;
        nine_x.pb(v % 10);
        carry = v / 10;
    }
    while (carry > 0) { nine_x.pb(carry % 10); carry /= 10; }

    // split 9X = H * 10^7 + lo
    int lo = 0, pw = 1;
    rep(i, 0, min((int)nine_x.size(), LOW_DIGITS)) {
        lo += nine_x[i] * pw;
        pw *= 10;
    }
    int ds_h = 0, trailing_nines = 0, h_len = 0;
    bool counting_nines = true;
    rep(i, LOW_DIGITS, (int)nine_x.size()) { // digits of H, least significant first
        ds_h += nine_x[i];
        h_len++;
        if (counting_nines && nine_x[i] == 9) trailing_nines++;
        else counting_nines = false;
    }
    // H + 1: the trailing 9s become 0s and the next digit increases by 1.
    // If H is all 9s (or empty, H = 0), H + 1 = 100...0, with digit sum 1.
    int ds_h1 = (trailing_nines == h_len) ? 1 : ds_h - 9 * trailing_nines + 1;

    for (int s = 1; ; s++) {
        int v = lo + s;            // < 2 * 10^7, so the carry into H is 0 or 1
        int low = v % LOW_MOD;
        if (low % 10 != 0) continue; // N = 9X + S must end in 0
        int ds = (v >= LOW_MOD ? ds_h1 : ds_h) + digitsum(low);
        if (ds <= s) {
            cout << s << '\n';
            break;
        }
    }
    return 0;
}
