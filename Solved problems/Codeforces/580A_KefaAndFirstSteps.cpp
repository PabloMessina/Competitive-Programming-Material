#include <bits/stdc++.h>
using namespace std;

#define MAXN 100000
int nums[MAXN];
int n;

int main() {
  scanf("%d", &n);
  int prev = -1;
  int maxlen = 0;
  int currlen = 0;
  while(n--) {
    int curr; scanf("%d", &curr);
    if (curr >= prev) {
      currlen++;      
    } else {
      currlen = 1;
    }
    if (maxlen < currlen) maxlen = currlen;
    prev = curr;    
  }
  printf("%d\n", maxlen);
  return 0;
}