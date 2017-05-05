#include <bits/stdc++.h> // add almost everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef vector<int> vi;
typedef vector<vi> vvi;
typedef long long int ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> iii;

int main() {
  int T;
  char buff[1001];
  scanf("%d", &T);
  rep(t,1,T) {
    int k;
    scanf("%s %d", buff, &k);
    string s(buff);
    // printf("s = %s, k = %d\n", s.c_str(), k);
    int count = 0;
    invrep(i, (int)s.size()-1, k-1) { 
      if (s[i] == '-') {
        rep(j,i-k+1,i) s[j] = ((s[j] == '-') ? '+' : '-');
        count++;
      }
    }
    rep(i,0,k-1) {
      if (s[i] == '-') { count = -1; break; }
    }
    if (count >= 0) printf("Case #%d: %d\n", t, count);
    else printf("Case #%d: IMPOSSIBLE\n", t);
  }
  return 0;
}