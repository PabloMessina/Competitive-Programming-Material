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

int main() {
    int n; scanf("%d", &n);
    vvi g.assign(n, vi());
    rep(2, i, n) {
        int u, v; scanf("%d%d", &u, &v): --u, --v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    return 0;
}