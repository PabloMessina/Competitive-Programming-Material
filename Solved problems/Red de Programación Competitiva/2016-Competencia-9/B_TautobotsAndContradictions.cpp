#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

#define MAXM 100
#define MAXN 15

int N, M;

char buff[10];
struct Stmt { int a; int b; char c; };
Stmt stmts[MAXM];
int arr[MAXN];

int main() {
  int T; scanf("%d", &T);
  rep(test, 1, T) {
    scanf("%d%d",&N,&M);
    rep(i, 0, M-1) {
      Stmt* s = &stmts[i];
      scanf("%d %d %c\n",&s->a,&s->b,&s->c);
    }

    // assignments
    int count = 0;
    memset(arr, 0, sizeof arr);
    int times = (1 << N);

    rep(k, 1, times) {
      // check if valid
      bool valid = true;
      rep(j,0,M-1) {
        Stmt s = stmts[j];
        if (arr[s.a]) {
          if ((arr[s.b] && s.c != 'T') ||
            (!arr[s.b] && s.c == 'T')) {
            valid = false;
            break;
          }
        } else {
          if ((arr[s.b] && s.c == 'T') ||
            (!arr[s.b] && s.c != 'T')) {
            valid = false;
            break;
          }
        }
      }
      if (valid) count++;

      // update assignment
      int carry = 1;
      int i = 0;
      while(true) {
        arr[i] += carry;
        if (arr[i] <= 1)
          break;
        else
          arr[i] = 0;
        ++i;
      }
    }

    // answer
    printf("Case #%d: %d\n", test, count);
  }
  return 0;
}