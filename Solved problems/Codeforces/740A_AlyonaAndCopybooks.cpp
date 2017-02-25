#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vii;
typedef long long int ll;
typedef pair<int,int> pii;

int n;
ll a,b,c;
ll memo[1000];
ll mincost(int k) {
  if (k == 0) return 0;
  if (memo[k] != -1) return memo[k];
  ll ans = LLONG_MAX;
  if (k >= 3) ans = min(ans, c + mincost(k-3));
  if (k >= 2) ans = min(ans, b + mincost(k-2));
  if (k >= 1) ans = min(ans, a + mincost(k-1));
  return memo[k] = ans;
}

int first_4_mult(int n) {
  if (n % 4 == 0) return n;
  return (n / 4 + 1) * 4;
};

int main() {  
  scanf("%d%I64d%I64d%I64d",&n,&a,&b,&c);
  memset(memo, -1, sizeof memo);
  ll ans = LLONG_MAX;
  for (int k = first_4_mult(n) - n;;k+=4) {
    ll tmp = mincost(k);
    if (tmp >= ans) break;
    ans = tmp;
  }
  printf("%I64d\n", ans);
  return 0;
}