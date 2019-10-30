// tags: adhoc, BFS by levels, modular arithmetics, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
typedef long long int ll;
// -------------------------------
const ll MOD = 1000000007;
int N, M;
vector<vector<pair<int,int>>> g;
vector<int> get_digits(int n) {
    vector<int> digits;
    while (n > 0) {
        digits.push_back(n % 10);
        n /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}
void add_edges(int u, int v, vector<int>& digits, int& ID) {
    int n = digits.size();
    for (int j = 0; j <= n-2; ++j) {
        g[u].emplace_back(ID, digits[j]);
        u = ID++;
    }
    g[u].emplace_back(v, digits[n-1]);
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;    
    g.resize(12 * M + N);
    int ID = N;
    rep(i,1,M) {
        int x, y; cin >> x >> y; --x, --y;
        vector<int> digits = get_digits(i);
        add_edges(x, y, digits, ID);
        add_edges(y, x, digits, ID);
    }
    g.resize(ID);
    vector<int> q, q_next;
    vector<int> depth(ID, -1);
    vector<pair<int,int>> scores(ID);
    vector<int> rank(ID);
    vector<ll> costs(ID);
    q.push_back(0);
    depth[0] = 0;
    rank[0] = 0;
    costs[0] = 0;
    auto cmp = [&scores](int i, int j) { return scores[i] < scores[j]; };

    while (1) {
        for (int u : q) {
            for (auto& p : g[u]) {
                int v, d; tie(v,d) = p;
                if (depth[v] == -1) {
                    depth[v] = depth[u] + 1;
                    scores[v] = { rank[u], d };
                    costs[v] = (costs[u] * 10LL + d) % MOD;
                    q_next.push_back(v);
                } else if (depth[v] == depth[u] + 1) {
                    auto score = make_pair(rank[u], d);
                    if (score < scores[v]) {
                        scores[v] = score;
                        costs[v] = (costs[u] * 10LL + d) % MOD;
                    }
                }
            }
        }
        if (q_next.empty()) break;
        sort(q_next.begin(), q_next.end(), cmp);
        int r = 0;
        int prev_u = q_next[0];
        rank[prev_u] = 0;
        for (int i = 1, n = q_next.size(); i < n; ++i) {
            int u = q_next[i];
            if (scores[prev_u] != scores[u]) r++;
            rank[u] = r;
            prev_u = u;
        }
        q.clear();
        q.swap(q_next);
    }
    rep(i,1,N-1) cout << costs[i] << '\n';    
    return 0;
}