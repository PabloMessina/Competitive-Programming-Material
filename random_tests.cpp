#include <bits/stdc++.h>
using namespace std;
#define MAXN 9999
#define umap unordered_map
#define rep(i,a,b) for(int i=a;i<=b;++i)

vector<int> get_primes(int n) {
  vector<bool> is_prime(n + 1, true);
  int limit = (int) floor(sqrt(n));
  rep (i,2,limit)
    if (is_prime[i])
      for (int j = i * i; j <= n; j += i)
        is_prime[j] = false;
  vector<int> primes;
  rep(i,2,n) if (is_prime[i]) primes.push_back(i);
  return primes;
}

void factorial_prime_factorization(int x, umap<int,int>& counts) {
  static vector<int> primes = get_primes(MAXN);

  for (int p : primes) {
    if (p > x) break;
    int count = 0;
    int n = x;
    while ((n /= p) > 0)
      count += n;
    if (count) counts[p] = count;
  } 
}

int main() {
  int x;
  while(scanf("%d",&x) == 1) {
    umap<int,int> counts;
    factorial_prime_factorization(x, counts);
    for(auto& kv : counts) {
      printf("   counts[%d] = %d\n", kv.first, kv.second);
    }
  }
  return 0;
}