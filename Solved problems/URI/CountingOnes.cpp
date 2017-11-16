// tags: math, combinatorics, bitwise operations
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll count_ones(ll x) {
    if (x == 0) return 0;
    int len = sizeof(x) * 8 - __builtin_clzll(x);
    ll xx = x;
    ll count = 0;
    for (ll i=len-1, bit = 1LL << (len-1); i>=0; i--, bit>>=1) {
        if (x & bit) {
            if (i > 0) {
                count += i << (i-1);
            }
            xx -= bit;
            count +=  xx + 1;
        }
    }
    return count;
}

int main() {
    ll a, b;    
    while (scanf("%lld %lld", &a, &b) == 2) {
        printf("%lld\n", count_ones(b) - count_ones(a-1));
    }
    return 0;
}