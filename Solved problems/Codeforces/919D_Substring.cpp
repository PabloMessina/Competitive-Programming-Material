// tags: graphs, DAG, DP, toposort
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N, M;
string S;
vector<vector<int>> g;

bool isDAG() {
    vector<int> indegree(N,0);
    rep(u,0,N) for (int v : g[u]) indegree[v]++;
    queue<int> q;
    int count = 0;
    rep(u,0,N) if (indegree[u] == 0) q.push(u);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        count++;
        for (int v : g[u]) if (--indegree[v] == 0) q.push(v);        
    }
    return count == N;
}

int freq[300000][26];
int memo[300000];
int dp(int u) {
    int& ans = memo[u];
    if (ans != -1) return ans;
    for (int v : g[u]) {
        dp(v);
        rep(i,0,26) freq[u][i] = max(freq[u][i], freq[v][i]);
    }
    freq[u][S[u]-'a']++;
    ans = 0;
    rep(i,0,26) ans = max(ans, freq[u][i]);
    return ans;
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> S;
    g.resize(N);
    set<pair<int,int>> used;
    rep(_,0,M) {
        int u, v; cin >> u >> v; --u, --v;
        if (u == v) {
            cout << "-1\n";
            return 0;
        }
        auto ret = used.emplace(u,v);
        if (ret.second) g[u].push_back(v);
    }
    if (not isDAG()) {
        cout << "-1\n";
        return 0;
    }
    memset(memo, -1, sizeof(int)*N);
    int ans = 0;
    rep(u,0,N) ans = max(ans, dp(u));
    cout << ans << '\n';
    return 0;
}