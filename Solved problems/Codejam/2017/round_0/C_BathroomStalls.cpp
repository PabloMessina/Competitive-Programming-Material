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

struct Interval {
    int i, j, m, max_, min_;
    Interval(int i_, int j_) {
        i = i_;
        j = j_;
        m = (i+j)/2;
        min_ = min(m-i,j-m);
        max_ = max(m-i,j-m);
    }
    bool operator<(const Interval& x) const {
        if (min_ != x.min_) return min_ > x.min_;
        if (max_ != x.max_) return max_ > x.max_;
        return m < x.m;
    }
};

int main() {
  int T, K, N;
  scanf("%d", &T);
  rep(t,1,T) {
      scanf("%d%d",&N,&K);
      set<Interval> intervals;
      intervals.insert(Interval(1,N));
      int min_, max_, m;
      rep(k,1,K) {
          const Interval& x = *intervals.begin();
          min_ = x.min_;
          max_ = x.max_;
          m = x.m;
          int i = x.i, j = x.j;        
          intervals.erase(x);
          if (m - i > 0) intervals.insert(Interval(i, m-1));
          if (j - m > 0) intervals.insert(Interval(m+1, j));
      }
      printf("Case #%d: %d %d\n", t, max_, min_);
  }  
  return 0;
}