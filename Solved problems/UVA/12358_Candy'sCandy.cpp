// tags: math, adhoc, modular arithmetic, divisors, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXF = 100000;
int F;
int C[MAXF];
void try_add_div(ll d, ll k, vector<int>& divs, int minC) {
    if (k < F+1) return;
    if (d % F != 0) return;
    if (d + d/F > minC) return;
    divs.push_back(d);
}
vector<int> get_divisors(ll totC, int minC) {
    vector<int> divs;
    divs.reserve(10000000);
    ll d1;
    for (d1 = F; d1 * d1 < totC; ++d1) {
        if (totC % d1 != 0) continue;
        ll d2 = totC / d1;
        try_add_div(d1, d2, divs, minC);
        try_add_div(d2, d1, divs, minC);
    }
    if (d1 * d1 == totC) try_add_div(d1, d1, divs, minC);
    return divs;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> F and F) {
        ll totC = 0;
        int minC = INT_MAX, maxC = 0;
        rep(i,0,F-1) {
            cin >> C[i];
            totC += C[i];
            minC = min(minC, C[i]);
            maxC = max(maxC, C[i]);
        }
        vector<int> divs = get_divisors(totC, minC);
        ll count = 0;
        if (divs.size() > 0) {
            sort(C, C+F);
            for (int d : divs) {
                int q = d/F;
                int base = d + q;
                if (base == minC and minC == maxC) {
                    count++; continue;
                }
                int r = (C[0] - base) % d;
                int rq = r % q;
                if (rq != 0) continue;
                int minq = (C[0] - base) / d;
                bool valid = true;
                rep(i,1,F-1) {
                    int r_i = (C[i] - base) % d;
                    if (r != r_i) { valid = false; break; }
                    minq = min(minq, (C[i] - base) / d);
                }
                if (!valid) continue;
                count += minq + 1;
            }
        }
        cout << count << '\n';
    }
    return 0;
} 