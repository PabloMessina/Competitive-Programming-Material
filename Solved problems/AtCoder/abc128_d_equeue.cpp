// tags: implementation, greedy
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int N, K; cin >> N >> K;
    vector<int> values(N), accL(N), accR(N);
    rep(i,0,N) cin >> values[i];
    int ans = 0;    
    rep(l,0,min(N,K)+1) {
        rep(r,0,min(N,K)-l+1) {
            int sum = 0;
            priority_queue<int> q;
            rep(i,0,l) {
                sum += values[i];
                if (values[i] < 0) q.push(-values[i]);
            }
            rep(i,0,r) {
                sum += values[N-i-1];
                if (values[N-i-1] < 0) q.push(-values[N-i-1]);
            }
            int k = K-l-r;
            while (q.size() and k--) {
                sum += q.top(); q.pop();
            }
            ans = max(ans, sum);
        }
    }
    cout << ans << '\n';
    return 0;
}