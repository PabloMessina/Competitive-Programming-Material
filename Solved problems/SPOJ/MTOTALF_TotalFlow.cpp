// tags: maxflow
#include <algorithm>
#include <bitset>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;
#define FOR(i,a,b) for(int i=a; i<=b; ++i)

typedef vector<int> vi;
typedef vector<vi> vvi;

#define MAXN 100
#define INF 1000000000

int N;
vvi adjList;
vi p;
int res[MAXN][MAXN];
int mf, f, s, t;

int charToId(char c) {
  if ('a' <= c && c <= 'z')
    return (int)(c - 'a');
  else
    return 26 + (int)(c - 'A');
}

void augment(int v, int minEdge) {
  if (v == s) { f = minEdge; return; }
  if (p[v] != -1) {
    augment(p[v], min(minEdge, res[p[v]][v]));
    res[p[v]][v] -= f; res[v][p[v]] += f;
  }
}

int main() {
  setvbuf(stdout, NULL, _IONBF, 0);
  scanf("%d\n", &N);
  adjList.assign(MAXN, vi());
  memset(res, 0, sizeof res);
  char buff1[100], buff2[100];
  FOR(i,1,N) {
    int w, a, b;
    scanf("%s %s %d", buff1,buff2, &w);
    a = charToId(buff1[0]);
    b = charToId(buff2[0]);
    adjList[a].push_back(b);
    adjList[b].push_back(a);
    res[a][b] += w;
    res[b][a] = 0;
  }
  mf = 0;
  s = charToId('A');
  t = charToId('Z');
  while (true) {
    f = 0;
    bitset<MAXN> vis; vis[s] = true;
    queue<int> q; q.push(s);
    p.assign(MAXN, -1);
    while (!q.empty()) {
      int u = q.front(); q.pop();
      FOR(j,0,(int)adjList[u].size() - 1) {
        int v = adjList[u][j];
        if (res[u][v] > 0 && !vis[v]) {
          vis[v] = true, q.push(v), p[v] = u;
          if (v == t) goto end_bfs;
        }
      }
    }
    end_bfs:
    augment(t, INF);
    if (f == 0) break;
    mf += f;
  } 
  printf("%d\n", mf);
  return 0;
}