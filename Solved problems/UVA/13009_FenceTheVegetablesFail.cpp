// tags: space reduction, range sum query, sweep line
#include <bits/stdc++.h>
#include <tr1/unordered_map>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define umap tr1::unordered_map
#define MAXN 100000
#define LSOne(s) (s & (-s))

typedef long long int ll;

int P,V;
struct Point { int x,y; };
Point plant_pts[MAXN];
Point fence_pts[MAXN];

struct Segment { int val, ymin, ymax, x; };
bool operator<(const Segment& a, const Segment& b) {
  return a.x < b.x;
}

struct FenwickTree {
  vector<int> ft;

  FenwickTree(int n) { ft.assign(n+1, 0); }

  int rsq(int b) {
    int sum = 0;
    for (; b; b -= LSOne(b)) sum += ft[b];
    return sum;
  }

  int rsq(int a, int b) {
    return rsq(b) - (a == 1 ? 0 : rsq(a-1));
  }

  void adjust(int k, int v) {
    for (; k < ft.size(); k += LSOne(k)) ft[k] += v;
  }

  void range_adj(int i, int j, int v) {
    adjust(i, v);
    adjust(j+1, -v);
  }
};


int main() {
  while (scanf("%d%d", &P, &V) == 2) {

    set<int> ycoords;
    umap<int,int> coordmap;
    
    rep(i,0,P-1) {
      int x,y; scanf("%d%d",&x,&y);
      plant_pts[i] = {x,y};
      ycoords.insert(y);
    }

    rep(i,0,V-1) {
      int x,y; scanf("%d%d",&x,&y);
      fence_pts[i] = {x,y};
      ycoords.insert(y);
    }

    int index = 1;
    for (int y : ycoords)
      coordmap[y] = index++;

    vector<Segment> segments;
    rep(i,0,P-1) {
      Point& p = plant_pts[i];
      int id = coordmap[p.y];
      segments.push_back({i+1, id, id, p.x});
    }
    rep(i,0,V-1) {
      int j = (i+1) % V;
      if (fence_pts[i].x == fence_pts[j].x) {
        int id1 = coordmap[fence_pts[i].y];
        int id2 = coordmap[fence_pts[j].y];
        if (id2 < id1) swap(id1, id2);
        segments.push_back({-1, id1, id2, fence_pts[i].x });
      }
    }
    sort(segments.begin(), segments.end());

    ll sum = 0;
    FenwickTree ft(P+V);
    for (Segment& seg : segments) {
      if (seg.val == -1) { // vertical segment
        if (ft.rsq(seg.ymin) > 0) {
          ft.range_adj(seg.ymin,seg.ymax-1,-1);
        } else {
          ft.range_adj(seg.ymin,seg.ymax-1, 1);
        }
      } else { // point
        if (ft.rsq(seg.ymin) == 0)
          sum += seg.val;
      }
    }

    printf("%lld\n", sum);

  }
  return 0;
}