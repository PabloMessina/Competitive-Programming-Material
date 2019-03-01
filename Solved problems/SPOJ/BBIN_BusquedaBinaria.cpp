// tags: binary search
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int nums[100000];
int main() {
    int N, Q; cin >> N >> Q;
    rep(i,0,N-1) cin >> nums[i];
    while(Q--) {
        int x; cin >> x;
        int l=0, r=N;
        while (l < r) {
            int m = (l+r)>>1;
            if (nums[m] >= x) r = m;
            else l = m+1;
        }
        if (l == N or nums[l] != x) cout << "-1\n";
        else cout << l << '\n';
    }
    return 0;
}