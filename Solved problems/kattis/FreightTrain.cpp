// tags: binary search
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<b;  ++i)
#define MAXW 10000
int N, W, L;
int pos[MAXW];

bool possible(int K) {
    int l = 0, r = K-1;
    int i = 0;
    int count = 0;
    while (l <= r) {
        ++count;
        if (i == W)
            break;
        if (pos[i] > r) {
            l = pos[i];
            r = min(l + K-1, N-1);
        } else {
            while(++i < W && pos[i] <= r) {}
            l = r+1;
            r = min(l + K-1, N-1);
        }    
    }
    return count <= L;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> N >> W >> L;
        rep (i, 0, W) {
            cin >> pos[i];
            pos[i]--;
        }
        int l = 1, r = N;
        while (l < r) {
            int m = (l + r) >> 1;
            if (possible(m)) {
                r = m;
            } else {
                l = m + 1;
            }
        }
        cout << l << '\n';
    }
    return 0;
}