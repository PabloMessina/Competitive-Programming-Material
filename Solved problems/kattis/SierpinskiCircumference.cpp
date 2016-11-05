#include <bits/stdc++.h>
using namespace std;

double a = log(3.0)/log(10.0);
double b = log(1.5)/log(10.0);
int main() {
  int n;
  int c = 1;
  while (scanf("%d", &n) == 1) {
    int x = (int)ceil(a + n * b);
    printf("Case %d: %d\n",c++,x);
  }
  return 0;
}