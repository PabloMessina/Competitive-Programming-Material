#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int N,K;

int main() {
  scanf("%d%d",&N,&K);
  int prev_l, prev_l2, curr_l;
  prev_l = -1;
  prev_l2 = -1;
  bool valid = true;

  rep(i,1,K) {
    scanf("%d", &curr_l);

    if (prev_l != -1) {
      int d = abs(curr_l - prev_l);
      if ((d != 1 && d != 2) || prev_l2 == curr_l) {
        valid = false;
        break;
      }
    }

    prev_l2 = prev_l;
    prev_l = curr_l;
  }

  if (valid) puts("S");
  else puts("N");

  return 0;
}