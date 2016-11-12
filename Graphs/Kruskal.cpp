/* ========================================= */
/* KRUSKAL ALGORITHM : Minimum Spanning Tree */
/* ========================================= */

typedef pair<int,int> pii;

// edge list
vector<pair<int,pii>> edge_list; // (weight, (u, v))
// num of nodes
int N;

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

int mst_cost() {
  sort(edge_list.begin(), edge_list.end());
  UnionFind uf(N);
  int cost = 0;
  for (auto& edge : edge_list) {
    int w = edge.first;
    int u = edge.second.first;
    int v = edge.second.second;
    if (!uf.isSameSet(u,v)) {
      cost += w;
      uf.unionSet(u, v);
    }
  }
  return cost;
}

