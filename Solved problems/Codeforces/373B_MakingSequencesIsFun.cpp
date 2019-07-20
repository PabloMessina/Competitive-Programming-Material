// tags: implementation, bases, math
#pragma GCC optimize("Ofast") // OPTIONAL: for faster execution
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
typedef long long int ll;

ll w, m, k;
int nd_m;

int num_digits(ll x) {
    int n = 0;
    while (x > 0) {
        n++; x /= 10;
    }
    return n;
}

ll pow10(int n) {
    ll x = 1;
    while (n-->0) x *= 10;
    return x;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> w >> m >> k;
    ll max_digits = w / k;
    if (max_digits == 0) {
        cout << "0\n";
    } else {
        int nd = num_digits(m);
        ll p10 = pow10(nd);
        if (p10 < m) p10 *= 10ll;
        ll d_count = 0;
        ll offset = m;
        ll x;
        while (true) {
            if (d_count + (p10 - offset) * nd >= max_digits) {
                x = floor ((max_digits - d_count) / (double)nd + offset);
                break;
            }
            d_count += (p10 - offset) * nd;
            offset = p10;
            p10 *= 10ll;
            nd++;
        }
        cout << x - m << '\n';
    }
    return 0;
}
