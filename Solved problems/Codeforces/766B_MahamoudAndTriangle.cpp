#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)

int main() {
    int n;
    scanf("%d", &n);
    int segs[n];
    rep(i,0,n-1) scanf("%d", &segs[i]);
    sort(segs, segs+n);
    bool possible = false;
    rep(i,0,n-3) {
        if (segs[i] + segs[i+1] > segs[i+2]) {
            possible = true; break;
        }
    }
    if (possible) puts("YES");
    else puts("NO");
    return 0;
}