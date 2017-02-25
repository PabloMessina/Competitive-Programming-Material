#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> pii;

int main() {
  int n,m;
  scanf("%d%d",&n,&m);
  int vals[n];
  int acc[n];
  int tmp = 0;
  rep(i,0,n-1) {
    scanf("%d", &vals[i]);
    tmp = acc[i] = vals[i] + tmp;
  }
  int ans = 0;
  rep(i,1,m) {
    int l,r; scanf("%d%d",&l,&r); --l,--r;
    int sum = acc[r] - (l>0? acc[l-1] : 0);
    if (sum > 0) ans += sum;
  }
  printf("%d", ans);
  return 0;
}