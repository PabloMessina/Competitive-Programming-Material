#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXN 5000

int N,L,C;
int lengths[MAXN];

int main() {
  scanf("%d%d%d",&N,&L,&C);
  rep(i,0,N-1) scanf("%d",&lengths[i]);
  sort(lengths, lengths + N);
  int ncols = (N / L) + ((N % L == 0) ? 0 : 1);
  int totwidth = 0;
  rep (c, 0, ncols-1) {
    totwidth += lengths[N-1-L*c];
  }
  if (totwidth <= C) puts("S");
  else puts("N");
  return 0;
}