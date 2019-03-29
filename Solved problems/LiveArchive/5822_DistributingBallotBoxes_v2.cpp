// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int pop[500000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while (true) {
        int N, B; cin >> N >> B;
        if (N==-1) break;
        rep(i,0,N-1) cin >> pop[i];
        int l = 1, r = *max_element(pop, pop+N);
        while (l < r) {
            int m = (l+r) >> 1;
            int c = B;
            rep(i,0,N-1) {
                c -= ((pop[i] / m) + (pop[i] % m > 0));
                if (c < 0) break;
            }
            if (c >= 0) r = m;
            else l = m + 1;
        }
        cout << l << '\n';
    }
    return 0;
}