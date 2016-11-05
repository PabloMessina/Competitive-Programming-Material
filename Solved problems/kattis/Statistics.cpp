#include <bits/stdc++.h>
using namespace std;

int main() {
  string line, tok;
  int _case = 1;
  int n;
  while (scanf("%d", &n) == 1) {
    int _min = -1, _max = -1;
    while (n--) {
      int x; scanf("%d", &x);
      _min = _min == -1 ? x : min(_min, x);
      _max = _max == -1 ? x : max(_max, x);
    }
    printf("Case %d: %d %d %d\n",_case++,_min,_max,_max-_min);
  }
  return 0;
}