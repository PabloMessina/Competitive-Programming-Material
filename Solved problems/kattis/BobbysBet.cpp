#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef long long ll;
ll fact[11];

double comb(int n, int k) {
  return fact[n]  / (double)(fact[k] * fact[n-k]);
}

int main() {
  int N, R, S, X, Y, W;

  fact[0] = 1;
  rep(i, 1, 10)
    fact[i] = i * fact[i-1];

  scanf("%d", &N);

  while(N--) {
    scanf("%d%d%d%d%d", &R, &S, &X, &Y, &W);
    double prob = 0;
    double fav = (S-R+1) / (double) S;
    rep(k, X, Y) {
      prob += comb(Y, k) * pow(fav, k) * pow(1.0 - fav, Y - k);
    }
    if (prob * W > 1.0)
      puts("yes");
    else
      puts("no");
  }
  return 0;
}