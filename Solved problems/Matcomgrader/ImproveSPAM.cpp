// tags: DP top-down, dfs
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD = 1000000007;
int N, L;
vector<vector<int>> g;
vector<ll> memo;
ll dp(int u) {
    ll& ans = memo[u];
    if (ans != -1) return ans;
    if (u >= L) return ans = 1;
    ans = 0;
    for (int v : g[u]) {
        ans = (ans + dp(v)) % MOD;
    }
    return ans;
}

vector<bool> vis;
void dfs(int u) {
    vis[u] = true;
    for (int v : g[u]) {
        if (vis[v]) continue;
        dfs(v);
    }
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> L;
    g.resize(N);
    rep(i,0,L) {
        int k; cin >> k;
        while (k--) {
            int j; cin >> j; --j;
            g[i].push_back(j);
        }
    }
    memo.assign(N, -1);
    ll bef = dp(0);
    vis.assign(N, 0);
    dfs(0);
    int aft = 0;
    rep(i,L,N) if (vis[i]) aft++;
    cout << bef << ' ' << aft << '\n';
    return 0;
}