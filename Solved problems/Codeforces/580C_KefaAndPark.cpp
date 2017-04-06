#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define MAXN 100000

int n,m;
int has_cat[MAXN];
vector<vector<int>> g;

int leaves_count = 0;

void dfs(int u, int p, int cats) {
    cats = has_cat[u] ? cats + 1 : 0;
    if (cats > m) return;
    if ((g[u].size() == 1 and u != 0) or g[u].size() == 0) {
        leaves_count++;
    } else {
        for (int v : g[u]) {
            if (v == p) continue;
            dfs(v, u, cats);
        }
    }    
}

int main() {    
    scanf("%d%d", &n, &m);
    g.assign(n, vector<int>());
    rep(i,0,n-1) scanf("%d", &has_cat[i]);
    rep(i,2,n) {
        int x, y; scanf("%d%d", &x, &y); --x, --y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    leaves_count = 0;
    dfs(0,-1,0);
    printf("%d\n",leaves_count);
    return 0;
}