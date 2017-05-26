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
bool deleted[MAXN];

ll memo[MAXN];

void dfs1(int u, int p, ll edge_cost) {
    parent[u] = p;
    if (p == -1) {
        memo[u] = 0;
        todelete[u] = false;
    } else {
        memo[u] = edge_cost;
        memo[u] = max(memo[u], memo[u] + memo[p]);        

        todelete[u] = (memo[u] > a[u]);
    }
    for (auto& v : g[u]) {
        if (v.first == p) continue;
        dfs1(v.first, u, v.second);
    }
}

int dfs2(int u, int p) {
    if (deleted[u]) return 0;
    deleted[u] = true;
    int c = 1;    
    for (auto& v : g[u]) {
        if (v.first == p) continue;
        c += dfs2(v.first, u);
    }
    return c;
}

int main() {
    scanf("%d", &n);
    rep(i, 0, n-1) scanf("%I64d", &a[i]);
    rep(i, 1, n-1) {
        int p; ll c;
        scanf("%d %I64d", &p, &c);
        --p;
        g[i].emplace_back(p, c);
        g[p].emplace_back(i, c);
    }
    
    memset(todelete, 0, sizeof(todelete));
    memset(deleted, 0, sizeof(deleted));
    dfs1(0, -1, 0);

    int count = 0;
    rep(i, 0, n-1) {
        if (todelete[i]) {
            count += dfs2(i, parent[i]);
        }
    }
    printf("%d\n", count);

    return 0;
}