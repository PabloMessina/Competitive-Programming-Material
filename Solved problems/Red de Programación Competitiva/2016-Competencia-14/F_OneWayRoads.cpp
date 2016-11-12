// tags: Max Flow, Bipartite Graph, Dinic, Binary Search
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
typedef pair<int,int> pii;

int N, M, V;
int s, t;
vector<pii> edge_list;

ll max_flow(int maxdeg) {
  Dinic din(V);
  rep (e, 0, M-1) {
    int a = M + edge_list[e].first;
    int b = M + edge_list[e].second;
    din.add_edge(s, e, 1);
    din.add_edge(e, a, 1);
    din.add_edge(e, b, 1);
  }
  rep(i,0,N-1) {
    din.add_edge(M+i, t, maxdeg);
  }
  return din.max_flow(s, t);
}

int main() {
  scanf("%d%d", &N,&M);
  edge_list.resize(M);
  rep(i,0,M-1) {   
    int a,b; scanf("%d%d", &a, &b); --a; --b;
    edge_list[i] = pii(a,b);
  }
  V = N+M+2;
  s = V-2;
  t = V-1;

  int dmin = 0, dmax = N;
  while (dmin < dmax) {
    int m = (dmin+dmax)/2;
    if (max_flow(m) == M)
      dmax = m;
    else
      dmin = m+1;
  }
  int ans = dmin;
  printf("%d\n", ans);
  return 0;
}