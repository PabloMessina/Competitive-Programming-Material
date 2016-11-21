// tags: greedy, polygon area
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a;i<=b;++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

const long double PI = acosl(-1);

int main() {
  int n; scanf("%d", &n);
  vector<int> scores(n);
  rep(i,0,n-1) scanf("%d", &scores[i]);
  sort(scores.begin(), scores.end());

  vector<int> radii(n);
  int l = n-1, r = 1;
  radii[0] = scores.back();
  invrep(i, n-2, 0) {
    if (i&1) radii[r++] = scores[i];
    else radii[l--] = scores[i];
  }

  long double delta = 2.0l * PI / n;
  long double angle;
  long double xs[n];
  long double ys[n];
  rep(i, 0, n-1) {
    angle = delta * i;
    xs[i] = radii[i] * cosl(angle);
    ys[i] = radii[i] * sinl(angle);
  }

  long double area = 0;
  for (int i = 0, j = n-1; i < n; j=i++) {
    area += (xs[i] + xs[j]) * (ys[i] - ys[j]);
  }
  area = fabsl(area * 0.5);
  printf("%.3Lf\n", area);
  return 0;
}