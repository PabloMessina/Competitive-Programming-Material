// tags: DP top-down, graphs
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
int N, M;
vector<vector<int>> g;
const int MAXN = 500;
int memo[MAXN][MAXN];
int cur_u, cur_v;
int dp_false=0, dp_true = 1;
set<int> path;
int dp(int i, int j) {
    int& ans = memo[i][j];
    if (ans >= dp_false) return ans;
    if (i == cur_u and j == N-1) return ans = dp_true;
    if (i == j) return ans = dp_false;
    if (i < j and i < cur_u) {
        for (int v : g[i]) {
            if (v != j and v <= cur_u) {
                if (dp(v, j) == dp_true) {
                    path.insert(i);
                    path.insert(j+N);
                    path.insert(v);
                    return ans = dp_true;
                }
            }
        }
    } else if (j < N-1) {
        for (int v : g[j+N]) {
            v -= N;
            if (v != i) {
                if (dp(i, v) == dp_true) {
                    path.insert(i);
                    path.insert(j+N);
                    path.insert(v+N);
                    return ans = dp_true;
                }
            }
        }
    }
    return ans = dp_false;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> M;
    g.resize(2*N);
    vector<pair<int,int>> middle_edges;
    rep(i,0,M) {
        int s, t; cin >> s >> t; --s, --t;
        g[s].push_back(t);
        if (s < N and t > N) {
            middle_edges.emplace_back(s, t);
        }
    }
    memset(memo, -1, sizeof memo);
    for (auto [u, v] : middle_edges) {
        cur_u = u, cur_v = v;
        if (dp(0, cur_v-N) == dp_true) {
            path.insert(0);
            path.insert(2*N-1);
            cout << path.size() << '\n';
            bool first = true;
            for (int x : path) {
                if (first) first = false;
                else cout << ' ';
                cout << (x+1);
            }
            cout << '\n';
            return 0;
        }
        dp_false += 2;
        dp_true += 2;
    }
    cout << "*\n";
    return 0;
}