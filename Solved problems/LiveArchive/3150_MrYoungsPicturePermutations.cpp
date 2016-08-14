// tags: hook numbers, gcd
#include <cstdio>
#include <cstring>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int matrix[6][31];
int length[5];
int factor[30];
int hook[30];
int t = 1;

int gcd(int a, int b) {
  while(b) { int aux = a; a = b; b = aux % b; }
  return a;
}

int main() {
  memset(matrix, -1, sizeof matrix);
  while (true) {
    int n; scanf("%d", &n);
    if (n==0) break;

    rep(r,0,n-1) {
      scanf("%d",&length[r]);
      rep(c,0,length[r]-1) matrix[r][c] = t;
    }

    int index = 0;
    rep(r,0,n-1) {
      rep(c,0,length[r]-1) {
        factor[index] = index + 1;
        hook[index] = length[r] - c;
        int rr = r;
        while(matrix[++rr][c] == t) hook[index]++;
        index++;
      }
    }

    rep(i,0,index-1) {
      rep(j,0,index-1) {
        int aux = gcd(factor[i], hook[j]);
        factor[i] /= aux;
        hook[j] /= aux;
      }
    }

    long long ans = 1;
    rep (i,0,index-1)
      ans *= factor[i];
    printf("%lld\n", ans);

    t++;
  }
  return 0;
}