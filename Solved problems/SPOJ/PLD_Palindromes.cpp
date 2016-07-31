  
#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

#define FOR(i,a,b) for(int i=a;i<=b;++i)

typedef unsigned long long int ull;
#define MAXN 30000
const ull a = 22695477;

int n;
int k;
string s;

ull ak;
ull rhf[MAXN];
ull rhb[MAXN];

int main() {
  scanf("%d\n",&k);
  getline(cin, s);
  n = s.size();

  // a raised to k power
  ak = 1;
  FOR (i, 1, k) ak *= a;

  // forward
  rhf[0] = 0;
  FOR (i, 0, k-1)
    rhf[0] = (rhf[0] * a + (s[i] - 'a'));
  for (int i = 1, lim = n - k; i <= lim; ++i)
    rhf[i] = rhf[i-1] * a + (s[i + k - 1] - 'a') - (s[i-1] - 'a') * ak;

  // backward
  rhb[n-1] = 0;
  for (int i = n-1; i >= n-k; --i)
    rhb[n-1] = (rhb[n-1] * a + (s[i] - 'a'));
  for (int i = n-2; i >= k-1; --i)
    rhb[i] = rhb[i+1] * a + (s[i - k + 1] - 'a') - (s[i + 1] - 'a') * ak;

  // count palindromes
  int count = 0;
  for (int i = 0, lim = n-k; i <= lim; ++i)
    if (rhf[i] == rhb[i+k-1]) count++;

  // answer
  printf("%d\n", count);
  return 0;
}