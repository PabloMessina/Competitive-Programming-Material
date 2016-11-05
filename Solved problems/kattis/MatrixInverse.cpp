#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int main() {
  int a,b,c,d;
  int aa,bb,cc,dd, den;
  int _case = 1;
  while (scanf("%d%d%d%d",&a,&b,&c,&d) == 4) {
    den = a*d - c*b;
    aa = d / den;
    bb = -b / den;
    cc = -c / den;
    dd = a / den;
    printf("Case %d:\n%d %d\n%d %d\n",_case,aa,bb,cc,dd);
    _case++;
  }
  return 0;
}