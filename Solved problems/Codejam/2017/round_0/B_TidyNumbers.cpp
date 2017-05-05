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
  // setvbuf(stdout, NULL, _IONBF, 0);  //debugging
  int T;
  scanf("%d\n", &T);
  rep(t,1,T) {
      string line;
      getline(cin, line);
      int n = line.size();
      int digits[n];
      rep(i,0,n-1) digits[i] = line[i] - '0';

      int work[n];
      int prev = 0;

      rep(i, 0, n-1) {
          if (digits[i] >= prev) {
              work[i] = digits[i];
          } else {
              int j = i;
              do {
                  j--;
                  work[j]--;
              } while (j > 0 and work[j-1] > work[j]);
              while (++j < n) {
                  work[j] = 9;
              }
              break;
          }
          prev = digits[i];
      }
      int i = (work[0] == 0) ? 1 : 0;
      printf("Case #%d: ", t);
      while (i < n) printf("%d", work[i++]);
      puts("");
  }
  return 0;
}