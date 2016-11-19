// tags: Greedy, priority queue with updates (tree set)
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define uset unordered_set
typedef pair<int,int> pii;
vector<uset<int>> g;

void update_node(set<pii>& pairs, int id, int prev_v, int next_v) {
  pairs.erase(pii(prev_v, id));
  pairs.insert(pii(next_v, id));
}

int main() {
  int N,M,A,B;
  scanf("%d%d%d%d", &N,&M,&A,&B);
  g.assign(N, uset<int>());
  rep(i,1,M) {
    int x,y; scanf("%d%d",&x,&y); --x,--y;
    g[x].insert(y);
    g[y].insert(x);
  }

  set<pii> pairs;
  rep(i,0,N-1) {
    pairs.insert(pii((int)g[i].size(), i));
  }

  while (true) {
    bool stop = true;

    while (!pairs.empty()) {
      auto it = pairs.begin();
      int comp = it->first;
      int id = it->second;
      if (comp < A) {
        stop = false;
        pairs.erase(*it);
        for (int v : g[id]) {
          int indegree = g[v].size();
          g[v].erase(id);
          update_node(pairs, v, indegree, indegree-1);
        }
      } else break;
    }

    while (!pairs.empty()) {
      auto it = pairs.rbegin();
      int incomp = (int)pairs.size() - it->first - 1;
      int id = it->second;
      if (incomp < B) {
        stop = false;
        pairs.erase(*it);
        for (int v : g[id]) {
          int indegree = g[v].size();
          g[v].erase(id);
          update_node(pairs, v, indegree, indegree-1);
        }
      } else break;
    }

    if (stop) break;
  }

  printf("%u\n", pairs.size());

  return 0;
}