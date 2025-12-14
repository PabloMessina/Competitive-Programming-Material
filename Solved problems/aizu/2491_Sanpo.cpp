// TODO: finish this problem
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
int N, T;
vector<vector<tuple<int,int,int,int>>> G; // G[i] = { j=neighbor, t=time, m=discoveries upper limit, v=value per discovery }
vector<ii> idx2pair;
vector<int> pair2idx;

int dp(int u, int p, int t) {
    assert (t >= 0);
    if (t == 0) return 0;
    int& ans = memo[u][t];
    if (ans != -1) return ans;

    ans = 0;

    if (G[u].size() == 0) return ans;
    if (G[u].size() == 1 && get<0>(G[u][0]) == p) return ans;
    if (G[u].size() >= 2) {
        int best = 0;
        for (auto [v, time, m, value] : G[u]) {
            if (v == p) continue;
            int sum = 0;
            rep(i,0,m+1) {
                sum = max(sum, i*value + dp(v, u, t - time*i));
            }
            best = max(best, sum);
        }
        ans = best;
    } else {
        auto [v, time, m, value] = G[u][0];
        int sum = 0;
        rep(i,0,m+1) {
            sum = max(sum, i*value + dp(v, u, t - time*i));
        }
        ans = sum;
    }
}

void init_idx2pair_pair2idx() {
    // run bfs to get idx2pair
    queue<ii> q;
    q.push({0, 0});
    while (!q.empty()) {
        auto [u, p] = q.front(); q.pop();
        int i = 0;
        for (auto [v, time, m, value] : G[u]) {
            if (v == p) continue;
            q.push({v,u});
            idx2pair.eb(u, i);
            ++i;
        }
    }
    // obtain pair2idx
    pair2idx.resize(N * N);
    rep(i,0,idx2pair.size()) {
        auto [u, j] = idx2pair[i];
        pair2idx[u*N + j] = i;
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> T;
    G.resize(N);
    rep(i,0,N-1) {
        int a, b, t, m, v;
        cin >> a >> b >> t >> m >> v;
        --a, --b;
        G[a].eb(b,t,m,v);
        G[b].eb(a,t,m,v);
    }
    init_idx2pair_pair2idx();
    return 0;
}