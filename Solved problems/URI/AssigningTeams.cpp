#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)

int main() {
  int nums[4];
  rep(i,0,3) scanf("%d", &nums[i]);
  sort(nums, nums+4);
  int diff = abs(nums[3]+nums[0] - nums[1]-nums[2]);
  printf("%d\n", diff);
  return 0;
}