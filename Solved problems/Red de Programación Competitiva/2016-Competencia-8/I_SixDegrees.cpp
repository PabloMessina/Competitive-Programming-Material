// tags: BFS
#include <cstdio>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> vi;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define MAXN 3010

int M;
int N;
char buff1[100], buff2[100];
vector<vi> g(MAXN, vi());
int steps[MAXN];

int bfs(int root) {
  memset(steps, -1, sizeof(steps[0]) * N);
  queue<int> q;
  q.push(root);
  steps[root] = 0;
  int count = 1;
  while (!q.empty()) {
    int u = q.front(); q.pop();
    for (int v : g[u])
      if (steps[v] == -1 && steps[u] + 1 <= 6) {
        count++;
        steps[v] = steps[u] + 1;
        if (steps[v] < 6) q.push(v);
      }
  }
  return count;
}

int id;
map<string, int> key2Id;

int findId(string& key) {
  auto it = key2Id.find(key);
  if (it == key2Id.end())
    return (key2Id[key] = id++);
  return it->second;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    scanf("%d", &M);

    id = 0;
    key2Id.clear();

    rep(i,1,M) {
      scanf("%s %s", buff1, buff2);
      string key1(buff1);
      string key2(buff2);
      // get ids
      int id1 = findId(key1);
      int id2 = findId(key2);
      if (id1 == id2) continue;
      // add edge to graph
      g[id1].push_back(id2);
      g[id2].push_back(id1);
    }

    N = id;

    int disc = 0;
    rep (root, 0, N-1)
      if (bfs(root) < N) disc++;

    // answer
    if (disc * 20 <= N)
      puts("YES");
    else
      puts("NO");

  }
  return 0;
}