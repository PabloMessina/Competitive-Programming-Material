// tags: MST, Minimum Spanning Tree

#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef long long int ll;
typedef pair<int,int> pii;
typedef vector<int> vi;

int N, M, L;
vector<pair<int,pii>> edge_list;

struct UnionFind {
  vi p, rank;
  int numSets;
  UnionFind(int n) {
    numSets = n;
    rank.assign(n,0);
    p.resize(n);
    rep(i,0,n-1) p[i] = i;
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) {
    if (!isSameSet(i, j)) {
      numSets--;
      int x = findSet(i), y = findSet(j);
      if (rank[x] > rank[y]) {
        p[y] = x;
      } else {
        p[x] = y;
        if (rank[x] == rank[y]) rank[y]++;
      }
    }
  }
};


int main() {
  scanf("%d%d%d", &N,&M,&L);

  ll cost_bef = 0;
  rep(i,1,M) {
    int u,v,w; scanf("%d%d%d", &u,&v,&w); --u, --v;
    edge_list.push_back(make_pair(w, pii(u,v)));
    if (i <= L) cost_bef += w;
  }

  ll mst_cost = 0;
  sort(edge_list.begin(), edge_list.end());
  UnionFind uf(N);
  for (auto& edge : edge_list) {
    int w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    if (!uf.isSameSet(u, v)) {
      mst_cost += w;
      uf.unionSet(u, v);
    }
  }

  if (uf.numSets == 1 && mst_cost <= cost_bef)
    puts("possible");
  else
    puts("impossible");

  return 0;
}