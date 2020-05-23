// tags: divide and conquer, dp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
const int MAXN = 100000;
int memo[MAXN+1];
int maxcalls(int n) {
    assert (n > 0);
    int& ans = memo[n];
    if (ans != -1) return ans;
    if (n == 1) return ans = 1;
    return ans = maxcalls(n/2) + maxcalls(n-n/2) + 1;
}

int a[MAXN];
void search(int l, int r, int k) {
    assert (maxcalls(r-l) >= k);
    assert (k > 0);
    if (k == 1) {
        rep(j,l,r) a[j] = j-l;
    } else {
        int m = (l+r)>>1;
        int k1 = min(maxcalls(m-l), k-2);
        int k2 = k-k1-1;
        search(l, m, k1);
        search(m, r, k2);
        rep(j,l,m) a[j] += r-m;
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int n, k; cin >> n >> k;
    memset(memo, -1, sizeof(memo));
    if (maxcalls(n) < k or (k&1) == 0) {
        cout << "-1\n";
    } else {
        search(0, n, k);
        rep(i,0,n) {
            if (i) cout << ' ';
            cout << a[i]+1;
        }
        cout << '\n';
    }
    return 0;
}