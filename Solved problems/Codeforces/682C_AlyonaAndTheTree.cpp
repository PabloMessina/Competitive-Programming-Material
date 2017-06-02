// tags: trees, DFS, DP bottom up
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

const int MAXN = (int)1e5;
int n;
ll a[MAXN];
vector<pair<int,ll>> g[MAXN];
int parent[MAXN];
bool todelete[MAXN];
ll memo[MAXN];

void dfs1(int u, ll edge_cost) {
    if (u == 0) {
        memo[u] = 0;
        todelete[u] = false;
    } else {
        memo[u] = max(edge_cost, edge_cost + memo[parent[u]]);
        todelete[u] = (memo[u] > a[u]);
    }
    for (auto& v : g[u]) {
        dfs1(v.first, v.second);
    }
}

int dfs2(int u) {
    if (todelete[u]) return 0;
    int c = 1;    
    for (auto& v : g[u]) {
        c += dfs2(v.first);
    }
    return c;
}

int main() {
    scanf("%d", &n);
    rep(i, 0, n-1) scanf("%I64d", &a[i]);
    rep(i, 1, n-1) {
        int p; ll c;
        scanf("%d %I64d", &p, &c); --p;
        parent[i] = p;
        g[p].emplace_back(i, c);
    }    
    memset(todelete, 0, sizeof(todelete));
    dfs1(0, 0);
    printf("%d\n",n - dfs2(0));
    return 0;
}