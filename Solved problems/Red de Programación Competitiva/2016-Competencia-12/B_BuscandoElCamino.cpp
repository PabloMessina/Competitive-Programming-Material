// tags: DP top down

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;

#define rep(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 4000

int N, E, S;
vector<pii> P;
double memo[MAXN][MAXN][2];
enum Where {LEFT, RIGHT};

double dist(int i, int j) {
  pii& a = P[i], b = P[j];
  int dx = a.first - b.first;
  int dy = a.second - b.second;
  return sqrt(dx*dx + dy*dy);
}

double solve(int l, int r, int w) {
  if (memo[l][r][w] >= -0.5)
    return memo[l][r][w];

  int l_next = (l+N-1) % N;
  int r_next = (r+1) % N;

  double ans = 1e10;
  if (w == LEFT) {
    if (l_next == S && r == S)
      ans = min(ans, dist(l, S));
    if (l_next != S)
      ans = min(ans, dist(l, l_next) + solve(l_next, r, LEFT));
    if (r != S)
      ans = min(ans, dist(l, r) + solve(l_next, r, RIGHT));    
  } else {
    if (r_next == S && l == S)
      ans = min(ans, dist(r, S));
    if (r_next != S)
      ans = min(ans, dist(r, r_next) + solve(l, r_next, RIGHT));
    if (l != S)
      ans = min(ans, dist(r, l) + solve(l, r_next, LEFT));
  }
  return memo[l][r][w] = ans;
}

int main() {
  scanf("%d%d%d",&N,&E,&S);
  --E; --S;  
  P.resize(N);
  rep(i,0,N-1)
    scanf("%d%d",&P[i].first,&P[i].second);

  int E_l = (E-1+N) % N;
  int E_r = (E+1) % N;

  rep(i, 0, N-1) rep(j, 0, N-1) memo[i][j][LEFT] = memo[i][j][RIGHT] = -1.0;
  double ans = 1e10;
  if (E_l != S)
    ans = min(ans, dist(E,E_l) + solve(E_l, E_r, LEFT));
  if (E_r != S)
    ans = min(ans, dist(E,E_r) + solve(E_l, E_r, RIGHT));
  if (E_l == S && E_r == S)
    ans = dist(E,S);
  printf("%.6lf\n", ans);

  return 0;
}