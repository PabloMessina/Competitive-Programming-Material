#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

const double pr = 4.342727686266486E-5;
double logfac[2502];

int main() {

  logfac[0] = 0;
  rep(i,1,2501) {
    logfac[i] = logfac[i-1] + log(i) / log(10);
  }

  int T; scanf("%d", &T);

  rep(test,1,T) {

    int A,B,C; scanf("%d%d%d",&A,&B,&C);
    double totA = 0, totB = 0, totC = 0;
    rep(i,0,A-1) {
      int k; scanf("%d", &k);
      totA += logfac[k];
    }
    rep(i,0,B-1) {
      int k; scanf("%d", &k);
      totB += logfac[k];
    }
    rep(i,0,C-1) {
      int k; scanf("%d", &k);
      totC += logfac[k];
    }

    printf("Case #%d: ", test);
    if (totA - pr >= totB && totA - pr >= totC) {
      puts("A");
    } else if (totB - pr >= totA && totB - pr >= totC) {
      puts("B");
    } else if (totC - pr >= totA && totC - pr >= totB) {
      puts("C");
    } else {
      puts("TIE");
    }
  }
  return 0;
}