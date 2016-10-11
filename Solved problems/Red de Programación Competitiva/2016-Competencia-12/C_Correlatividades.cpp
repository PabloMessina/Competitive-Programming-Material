// tags: DAG, BFS
#include <bits/stdc++.h>
#include <tr1/unordered_set>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 50000

typedef vector<int> vi;
typedef std::tr1::unordered_set<int> int_uset;

int N, M;
vector<vi> gout;
vector<vi> gin;
vector<int_uset> prereqs;
bool done[MAXN];

void propagate(int c, int& count) {
  done[c] = true;

  if (prereqs[c].size() == 0) {
    queue<int> q;
    count++;
    q.push(c);

    while(!q.empty()) {
      int u = q.front(); q.pop();
      for (int v : gout[u]) {
        prereqs[v].erase(u);
        if (prereqs[v].size() == 0 && done[v]) {
          count++;
          q.push(v);
        }
      }
    }
  }
}

int main() {
  scanf("%d%d",&N,&M);
  gout.assign(N, vi());
  gin.assign(N,vi());
  prereqs.assign(N, int_uset());  
  memset(done, false, sizeof(false)*N);

  rep(i,1,M) {
    int a, b; scanf("%d%d", &a, &b); --a, --b;
    gout[a].push_back(b);
    gin[b].push_back(a);
    prereqs[b].insert(a);    
  }

  int count = 0;
  rep(i,1,N) {
    int c; scanf("%d", &c); --c;
    propagate(c, count);
    printf("%d\n", count);
  }

  return 0;
}