#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

int main() {
  int minx = 1000, miny = 1000, maxx = 1, maxy = 1;
  set<pair<int,int>> coords;
  rep(i,1,3) {
    int x,y; scanf("%d%d", &x, &y);
    minx = min(minx, x);
    miny = min(miny, y);
    maxx = max(maxx, x);
    maxy = max(maxy, y);
    coords.emplace(x,y);
  }
  if (!coords.count({minx, miny})) {
    printf("%d %d", minx, miny);
    return 0;
  }
  if (!coords.count({minx, maxy})) {
    printf("%d %d", minx, maxy);
    return 0;
  }
  if (!coords.count({maxx, miny})) {
    printf("%d %d", maxx, miny);
    return 0;
  }
  printf("%d %d", maxx, maxy);
  return 0;
}
