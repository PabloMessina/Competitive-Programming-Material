#include <bits/stdc++.h>
using namespace std;
typedef vector<int> vi;

struct UnionFind {
  vi p, rank, setSize;
  int numSets;
  UnionFind(int n) {
    numSets = n; setSize.assign(n, 1); rank.assign(n, 0); p.resize(n);
    rep(i,0,n-1) p[i] = i;
  }
  int findSet(int i) { return (p[i] == i) ? i : (p[i] = findSet(p[i])); }
  bool isSameSet(int i, int j) { return findSet(i) == findSet(j); }
  void unionSet(int i, int j) { 
    if (!isSameSet(i, j)) {
      numSets--; 
      int x = findSet(i), y = findSet(j);
      // rank is used to keep the tree short
      if (rank[x] > rank[y]) {
        p[y] = x; setSize[x] += setSize[y];
      } else {
        p[x] = y; setSize[y] += setSize[x];
        if (rank[x] == rank[y]) rank[y]++;
      }
    }
  }
  int numDisjointSets() { return numSets; }
  int sizeOfSet(int i) { return setSize[findSet(i)]; }
};