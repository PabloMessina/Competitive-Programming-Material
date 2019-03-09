// tags: bitwise operators, bit manipulation, implementation
#include <bits/stdc++.h>
using namespace std;
int reverse_bits(int x) {
    int v = 0;
    while (x) v <<= 1, v |= x&1, x >>= 1;
    return v;
}
int main() {
    int n; cin >> n; cout << reverse_bits(n);
    return 0;
}