// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N, X;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> X;
    vector<int> A(N);
    rep(i,0,N) cin >> A[i];
    int ans = 1;
    int i = 0;
    while (i < N) {
        int len = 1;
        while (i+1 < N and A[i+1] - A[i] <= X) ++i, ++len;
        ans = max(ans, len);
        ++i;
    }
    cout << ans << '\n';
    return 0;
}