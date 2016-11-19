// tags: constraint propagation, BFS
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define uset unordered_set
#define MAXN 100000

int N,M,A,B;
vector<uset<int>> g;
vector<bool> inside;
int curr, nxt;
int remain[2][MAXN];

int main() {
  scanf("%d%d%d%d", &N,&M,&A,&B);
  g.assign(N, uset<int>());
  inside.assign(N, true);

  rep(i,1,M) {
    int x,y; scanf("%d%d", &x, &y); --x, --y;
    g[x].insert(y);
    g[y].insert(x);
  }

  curr = 0;
  rep(i,0,N-1) remain[curr][i] = i;
  queue<int> q;
  int comp, incomp;

  while (true) {
    nxt = 1 - curr;
    bool stop = true;
    int N_bef = N;

    rep(i,0,N-1) {
      int x = remain[curr][i];
      if (inside[x]) {
        comp = g[x].size(), incomp = N - 1 - (int)g[x].size();
        if (comp < A or incomp < B) {
          stop = false;
          inside[x] = false;
          q.push(x);
          while(!q.empty()) {
            int u = q.front(); q.pop();
            N--;
            for (int v : g[u]) {
              if (inside[v]) {
                g[v].erase(u);
                comp = g[v].size(), incomp = N - 1 - (int)g[v].size();
                if (comp < A or incomp < B) {
                  inside[v] = false;
                  q.push(v);
                }                
              }
            }
          }
        }        
      }
    }

    if (stop) break;

    int j = 0;
    rep(i,0,N_bef-1) if (inside[remain[curr][i]]) remain[nxt][j++] = remain[curr][i];
    curr = nxt;
  }

  printf("%d\n", N);

  return 0;
}