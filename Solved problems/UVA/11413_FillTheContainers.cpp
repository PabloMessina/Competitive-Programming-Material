// tags: binary search
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <=b; ++i)
// --------------------------------------
int cap[1000];
int N, M;

bool possible(int maxcap) {
    int x = M-1;
    int r = maxcap;
    rep(i,0,N-1) {
        r -= cap[i];
        if (r < 0) {
            r = maxcap - cap[i];
            assert (r >= 0);
            if (--x < 0) return false;
        }
    }
    return true;
}

int main() {    
    while (cin >> N >> M) {
        rep(i,0,N-1) cin >> cap[i];
        int l = *max_element(cap, cap+N), r = accumulate(cap, cap+N, 0);
        while (l < r) {
            int m = (l+r) >> 1;
            if (possible(m)) r = m;
            else l = m+1;
        }
        cout << l << '\n';
    }
    return 0;
}