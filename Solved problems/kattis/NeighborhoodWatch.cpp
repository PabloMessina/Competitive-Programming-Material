// tags: implementation, two pointers
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int N, K;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> K;
    vector<bool> watch(N, false);
    rep(i,0,K) {
        int j; cin >> j; --j;
        watch[j] = true;
    }
    ll count = 0;
    int j = 0;
    rep(i,0,N) {
        while (j < i or (j < N and not watch[j])) ++j;
        count += N - j;
    }
    cout << count << '\n';
    return 0;
}