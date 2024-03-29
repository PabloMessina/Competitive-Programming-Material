// tags: greedy, priority queue
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const int MAXN = 1000;
const int MAXK = 1000000;
int R,C,K; ll P;
ll matrix[MAXN][MAXN];
ll rvals[MAXK+1], cvals[MAXK+1];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> R >> C >> K >> P;
    rep(r,0,R) rep(c,0,C) cin >> matrix[r][c];
    priority_queue<ll> rq, cq;
    rep(r,0,R) {
        ll sum = 0;
        rep(c,0,C) sum += matrix[r][c];
        rq.push(sum);
    }
    rep(c,0,C) {
        ll sum = 0;
        rep(r,0,R) sum += matrix[r][c];
        cq.push(sum);
    }
    rep(i,1,K+1) {
        ll x = rq.top();
        rvals[i] = rvals[i-1] + x;
        rq.pop();
        rq.push(x - P * C);
    }
    rep(i,1,K+1) {
        ll x = cq.top();
        cvals[i] = cvals[i-1] + x;
        cq.pop();
        cq.push(x - P * R);
    }
    ll ans = -LLONG_MIN;
    for (ll k = 0; k <= K; ++k) {
        ans = max(ans, rvals[k] + cvals[K-k] - k*(K-k)*P);
    }    
    cout << ans << '\n';
    return 0;
}