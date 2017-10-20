// tags: DP top-down, graphs, DAG
// DISCLAIMER: only tested with example
#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned int uint;
typedef long long int ll;
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;
typedef pair<double, int> pdi;
typedef pair<ll, int> lli;
// -------------------------------

// map names to ids
int ID = 0;
map<string,int> name2id;
int get_id(string& name) {
    auto it = name2id.find(name);
    if (it == name2id.end())
        return name2id[name] = ID++;
    return it->second;
}

const int MAXI = 100000;
int times[MAXI]; 
vector<vi> g(MAXI); // dependency graph

// top down DP
int memo[MAXI];
int total_time(int u) {
    if (memo[u] >= 0) return memo[u];
    int t = 0;
    for (int v : g[u]) {
        t = max(t, total_time(v));
    }
    return memo[u] = t + times[u];
}

int main() {
    int I;
    scanf("%d", &I);

    // read input and build graph
    char buff[30];
    rep(i,0,I-1) {
        int t, d;
        scanf("%d%d%s", &t, &d, buff);
        string uname(buff);
        int u = get_id(uname);
        times[u] = t;
        rep(j,1,d) {
            scanf("%s", buff);
            string vname(buff);
            int v = get_id(vname);
            g[u].push_back(v);
        }
    }

    // find answer with top-down DP over the dependency graph
    int N;
    scanf("%d", &N);
    memset(memo, -1, sizeof memo);
    int ans = 0;
    while (N--) {
        scanf("%s", buff);
        string name(buff);
        int id = get_id(name);
        ans = max(ans, total_time(id));
    }
    printf("%d\n", ans);
    return 0;
}