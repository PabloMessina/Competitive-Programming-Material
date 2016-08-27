#include <bits/stdc++.h>
#include <climits>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXN 100000

int nums[MAXN];
bool candidate[MAXN];

int main() {
  int n; scanf("%d", &n);
  int minn = INT_MAX;
  int maxn = INT_MIN;
  int count = 0;

  rep(i,0,n-1) {
    scanf("%d", &nums[i]);
    if (nums[i] >= maxn) {
      candidate[i] = true;
    }
    if (nums[i] > maxn)
      maxn = nums[i];
  }
  invrep(i, n-1, 0) {
    if ((i == n-1 || nums[i] < minn)) {
      minn = nums[i];
      if (candidate[i]) count++;
    }
  }
  printf("%d", count);
  return 0;
}
