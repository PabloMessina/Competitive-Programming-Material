// tags: BFS, preprocessing, DP, top-down, Knapsack
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 200
#define MAXB 10000
typedef vector<int> vi;

int D,P,R,B,N, CN;
int price[MAXN];
int gain[MAXN][2];
int cost[MAXN];
int party[MAXN];

vector<vi> g;
bool vis[MAXN];
int memo0[MAXN][MAXB+1];
int memo1[MAXN][MAXB+1];

int idx;

void bfs(int s) {

  queue<int> q; q.push(s);
  vis[s] = true;
  gain[idx][party[s]] = -1;
  gain[idx][1-party[s]] = 1;
  cost[idx] = price[s];

  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u]) if (!vis[v]) {
      vis[v] = true;
      cost[idx] += price[v];
      gain[idx][party[v]]--;
      gain[idx][1-party[v]]++;
      q.push(v);
    }
  }
}

int dp0(int i, int c) {
  if (memo0[i][c] != -1) return memo0[i][c];
  int ans = 0;  
  if (i == CN-1) { // last
    if (cost[i] <= c && gain[i][0] > 0) {
      ans = gain[i][0];
    }
  } else {
    ans =  dp0(i+1, c);
    if (cost[i] <= c && gain[i][0] > 0) {
      ans = max(ans, gain[i][0] + dp0(i+1, c-cost[i]));
    }
  }
  return memo0[i][c] = ans;
}

int dp1(int i, int c) {
  if (memo1[i][c] != -1) return memo1[i][c];
  int ans = 0;  
  if (i == CN-1) { // last
    if (cost[i] <= c && gain[i][1] > 0) {
      ans = gain[i][1];
    }
  } else {
    ans =  dp1(i+1, c);
    if (cost[i] <= c && gain[i][1] > 0) {
      ans = max(ans, gain[i][1] + dp1(i+1, c-cost[i]));
    }
  }
  return memo1[i][c] = ans;
}


int main() {
  while(scanf("%d%d%d%d", &D,&P,&R,&B) == 4) {
    N = D+P;
    g.assign(N, vi());
    rep(i, 0, D-1) {
      scanf("%d", &price[i]);
      party[i] = 0;
    }
    rep(i, 0, P-1) {
      scanf("%d", &price[i+D]);
      party[i+D] = 1;
    }
    rep(i, 1, R) {
      int x,y; scanf("%d%d",&x,&y); --x, --y;
      g[x].push_back(y+D);
      g[y+D].push_back(x);
    }
    //
    idx = 0;
    memset(vis, 0, sizeof vis);
    rep (i, 0, N-1) if (!vis[i]) {
      bfs(i); idx++;
    }
    CN = idx;
    //
    memset(memo0, -1, sizeof memo0);
    memset(memo1, -1, sizeof memo1);
    int ans0 = D + dp0(0, B);
    int ans1 = P + dp1(0, B);
    printf("%d %d\n", ans0, ans1);
  }
  return 0;
}