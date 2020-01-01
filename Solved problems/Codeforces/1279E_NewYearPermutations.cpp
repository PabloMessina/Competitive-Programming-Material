// tags: dp, combinatorics, math, lexicographic recovery
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
int n; ll k;
int p[50];
ll fact[51];

ll add(ll x, ll y) {
    if (x > LLONG_MAX - y) return LLONG_MAX;
    return x + y;
}
ll mul(ll x, ll y) {
    if (x > LLONG_MAX / y) return LLONG_MAX;
    return x * y;
}

ll memo[51];
ll dp(int n) {
    ll& ans = memo[n];
    if (ans != -1) return ans;
    if (n == 0) return ans = 1;
    ans = 0;
    rep(s,1,n+1) {
        ans = add(ans, mul(s-2 >= 0 ? fact[s-2] : 1LL, dp(n - s)));
    }
    return ans;
}

bool valid(int i, int x, int s) {
    static vector<bool> vis;
    vis.assign(n, 0);
    vis[i] = true;
    p[i] = x;
    int u = i;
    int count = 0;
    while (p[u] != -1) {
        count++;
        u = p[u]-1;
        if (vis[u]) {
            p[i] = -1;
            return (u == i and count == s);
        }
        vis[u] = true;
    }
    p[i] = -1;
    return true;
}

void fill_block(int offset, int s, ll k) {
    p[offset] = s + offset;
    vector<bool> used(s, 0);
    used[s-1] = true;
    rep(i,1,s) {
        rep(j,0,s) {
            if (not used[j] and valid(offset + i, offset + j + 1, s)) {
                ll w = s-i-2 >= 0 ? fact[s-i-2] : 1;
                if (w > k) {
                    p[offset + i] = offset + j + 1;
                    used[j] = true;
                    break;                    
                } else {
                    k -= w;
                }
            }
        }
    }
}

bool search(int i, ll k) {
    if (i == n) return true;
    rep(s, 1, n-i+1) {
        ll ways = mul((s >= 2 ? fact[s-2] : 1LL), dp(n - i - s));
        if (ways < k) k -= ways;
        else {
            ll w = dp(n - i - s);
            fill_block(i, s, (k-1)/w);
            k -= mul((k-1)/w, w);
            return search(i + s, k);
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int t; cin >> t;
    memset(memo, -1, sizeof memo);
    fact[0] = 1;
    rep(i,1,51) fact[i] = mul(fact[i-1], i);
    while (t--) {
        cin >> n >> k;
        memset(p, -1, sizeof p);
        if (search(0, k)) {
            rep(i,0,n) {
                if (i) cout << ' ';
                cout << p[i];
            }
            cout << '\n';
        } else {
            cout << "-1\n";
        }
    }
    return 0;
}