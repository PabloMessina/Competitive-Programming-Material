#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 30
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define invrep(i,b,a) for(int i=b;i>=a;--i)
int sizes[MAXN];

int max_i(int n) {
  int i = n-1;
  int m = sizes[i];
  invrep(j, n-2, 0) {
    if (m < sizes[j]) {
      m = sizes[j];
      i = j;
    }
  }
  return i;
}

void invert(int i, int j) {
  while (i < j) {
    int aux = sizes[i];
    sizes[i] = sizes[j];
    sizes[j] = aux;
    i++; j--;
  }
}

int main() {
  int n;
  while(true) {
    scanf("%d", &n);
    if (n == 0) break;
    rep (i,0,n-1) scanf("%d", &sizes[i]);
    vector<int> flips;
    while (n) {
      int mi = max_i(n);
      if (mi < n-1) {
        if (mi > 0) {
          invert(0, mi);
          flips.push_back(mi + 1);
        }
        invert(0, n-1);
        flips.push_back(n);
      }
      n--;
    }
    printf("%d", (int)flips.size());
    for (int f : flips) printf(" %d", f);
    puts("");
  }

}