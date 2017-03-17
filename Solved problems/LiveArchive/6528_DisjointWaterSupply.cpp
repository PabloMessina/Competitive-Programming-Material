// tags: DP, DAG
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
typedef vector<int> vi;

int C,P;
vector<vi> g;
int memo[1000][1000];
int dp(int i, int j) {
    if (i > j) swap(i,j);
    if (memo[i][j] != -1)
        return memo[i][j];
    int ans;
    if (i == 0 or j == 0)
        ans = true;
    else if (i == j)
        ans = false;
    else {
        ans = false;
        for (int v : g[j])
            if (dp(i, v)) {
                ans = true; break;
            }                
    }
    return memo[i][j] = ans;
}

int main() {
    while(scanf("%d%d",&C,&P)==2) {
        g.assign(C,vi());
        rep(i,1,P) {
            int u,v; scanf("%d%d",&u,&v); --u,--v;
            g[v].push_back(u);
        }
        int count = 0;
        memset(memo, -1, sizeof memo);
        rep(i,0,C-2) rep(j,i+1,C-1) 
            if (dp(i,j)) count++;
        printf("%d\n", count);
    }
    return 0;
}