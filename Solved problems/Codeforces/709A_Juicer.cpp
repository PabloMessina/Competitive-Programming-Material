#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a;i<=b;++i)

int N,B,D;

int main() {
  scanf("%d%d%d",&N,&B,&D);
  int total = 0;
  int count = 0;
  rep(i,1,N) {
    int a; scanf("%d", &a);
    if (a <= B) {
      total += a;
      if (total > D) {
        total = 0;
        count++;
      }
    }
  }
  printf("%d\n", count);
  return 0;
}