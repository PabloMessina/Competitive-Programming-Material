#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

int log2(int x) {
  return sizeof(x) * 8 - __builtin_clz(x) - 1;
}

int main() {
  int n; scanf("%d", &n);
  int len = sizeof(n) * 8 - __builtin_clz(n);
  int n2 = 0;
  invrep(i, len-1, 0) {
    if ((1 << i) & n) {
      n2 |= (1 << (len - 1 - i));
    }
  }
  printf("%d", n2);
  return 0;
}
