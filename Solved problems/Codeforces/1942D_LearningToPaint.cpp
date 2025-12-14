#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
int a[1000][1000];
int n, k;
bool visited[1000];
vector<ll> memo[1000];

vector<ll> &dp(int i) {
    assert(i < n);
    if (visited[i]) return memo[i];
    visited[i] = true;
    priority_queue<tuple<ll,int,int,bool>> pq; // (score, memo index, vector index, add interval)
    if (i == n-1) {
        pq.emplace(0, -1, -1, false);
    } else {
        vector<ll>& v = dp(i+1);
        pq.emplace(v[0], i+1, 0, false);
    }
    rep(j,i,n) {
        if (j >= n-2) {
            pq.emplace(a[i][j], -1, -1, false);
        } else {
            vector<ll>& v = dp(j+2);
            pq.emplace(a[i][j] + v[0], j+2, 0, true);
        }
    }
    vector<ll>& ans = memo[i];
    while (pq.size() > 0 and ans.size() < k) {
        auto [score, idx, vidx, add_interval] = pq.top();
        pq.pop();
        ans.push_back(score);
        if (idx != -1) {
            if (vidx+1 < memo[idx].size()) {
                ll tmp = memo[idx][vidx+1];
                if (add_interval) tmp += a[i][idx-2];
                pq.emplace(tmp, idx, vidx+1, add_interval);
            }
        }
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> k;
        rep(i,0,n) rep(j,i,n) cin >> a[i][j];
        rep(i,0,n) visited[i] = false;
        rep(i,0,n) memo[i].clear();
        vector<ll>& ans = dp(0);
        rep(i,0,ans.size()) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}