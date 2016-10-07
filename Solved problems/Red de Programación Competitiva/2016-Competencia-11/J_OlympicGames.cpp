#include <bits/stdc++.h>
using namespace std;

typedef long long int ll;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)
#define MAXN 100000
#define INF 1000005

// ---------
struct Point {
  ll x, y; int id;
};
bool operator<(const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

// ---------
struct Fraction {
  ll a, b;
  Fraction (ll _a, ll _b) {
    if (_b < 0) _a *= -1, _b *= -1;
    a = _a, b = _b;
  }
  Fraction() {}
  double to_double() const {
    return (double)a / (double)b;
  }
};
bool operator<(const Fraction& f1, const Fraction& f2) {
  return f1.a * f2.b < f1.b * f2.a;
}
bool operator<=(const Fraction& f1, const Fraction& f2) {
  return f1.a * f2.b <= f1.b * f2.a;
}
bool operator==(const Fraction& f1, const Fraction& f2) {
  return f1.a == f2.a && f1.b == f2.b;
}

// ---------
int N;
ll skm[MAXN];
ll skn[MAXN];
ll ftm[MAXN];
ll ftn[MAXN];
Point dual_sk[MAXN];
Point dual_ft[MAXN];
bool golden[MAXN];

// =======================
// Convex-Hull fuctions
// =======================

ll isLeft(Point& o, Point& a, Point& b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

/* Get lower hull of skill dual points. This matches skill upper envelope */
vector<Point> sk_lower_hull() {
  // sort dual skill points
  sort(dual_sk, dual_sk + N);
  // build lower hull
  int k = 0;
  vector<Point> lh(N);
  rep(i, 0, N-1) {
    while(k >= 2 && isLeft(lh[k-2], lh[k-1], dual_sk[i]) < 0) k--;
    // add dual point unless it's vertically above the previous one
    if (k == 0 || !(lh[k-1].x == dual_sk[i].x && lh[k-1].y < dual_sk[i].y))
      lh[k++] = dual_sk[i];
  }
  lh.resize(k);
  return lh;
}

/* Get upper hull of fatigue dual points. This matches fatigue lower envelope */
vector<Point> ft_upper_hull() {
  // sort dual fatigue points
  sort(dual_ft, dual_ft + N);
  // build upper hull
  int k = 0;
  vector<Point> uh(N);
  invrep(i, N-1, 0) {
    while(k >= 2 && isLeft(uh[k-2], uh[k-1], dual_ft[i]) < 0) k--;
    // add dual point unless it's vertically below the previos one
    if (k == 0 || !(uh[k-1].x == dual_ft[i].x && uh[k-1].y > dual_ft[i].y))
      uh[k++] = dual_ft[i];
  }
  uh.resize(k);
  return uh;
}

// ==================================

/* Get a map from intervals to athlete ids*/
map<pair<Fraction,Fraction>,set<int>> get_intervals_map(vector<Point>& pts, ll* ms, ll* ns) {

  Fraction prev_t(-INF, 1);
  set<int> ids;
  int prev_id = -1;
  int curr_id;
  map<pair<Fraction,Fraction>,set<int>> intvmap;

  for (Point& p : pts) {
    curr_id = p.id;
    if (prev_id == -1) {
      ids.insert(curr_id);
    } else {
      if (ms[curr_id] == ms[prev_id]) { // same line
        ids.insert(curr_id);
      } else {
        Fraction t (
          ns[curr_id] - ns[prev_id],
          ms[prev_id] - ms[curr_id]
        );
        intvmap[std::make_pair(prev_t, t)].insert(ids.begin(), ids.end());
        ids.clear();
        ids.insert(curr_id);
        prev_t = t;
      }
    }
    prev_id = curr_id;
  }

  Fraction end(INF, 1);
  intvmap[std::make_pair(prev_t, end)].insert(ids.begin(), ids.end());

  // return interval map
  return intvmap;
}

Fraction TIME_ZERO(0, 1);

/* Count golden athletes by checking intersections between skill intervals
and fatigue intervals. Intervals are swept linearly by shifting 2 pointers. */
int count_golden(
  map<pair<Fraction,Fraction>,set<int>>& sk_intvmap,
  map<pair<Fraction,Fraction>,set<int>>& ft_intvmap) {

  int count = 0;
  memset(golden, false, sizeof(bool)*N);

  auto start_kv2 = ft_intvmap.begin();
  for (auto& kv1 : sk_intvmap) {
    const Fraction& start1 = kv1.first.first;
    const Fraction& end1 = kv1.first.second;
    const set<int>& ids1 = kv1.second;

    bool first = true;

    for (auto kv2 = start_kv2; kv2 != ft_intvmap.end(); ++kv2) {
      const Fraction& start2 = kv2->first.first;
      const Fraction& end2 = kv2->first.second;
      const set<int>& ids2 = kv2->second;

      Fraction max_start = std::max(start1, start2);
      Fraction min_end = std::min(end1, end2);

      if (max_start <= min_end) {
        if (first && end1 <= end2) {
          first = false;
          start_kv2 = kv2;
        }
        if (TIME_ZERO <= min_end) {
          for (int id : ids1) {
            if (golden[id]) continue;
            if (ids2.find(id) != ids2.end()) {
              golden[id] = true;
              count++;
            }
          }
        }
      }
    }
  }

  return count;
}

int main() {
  while (scanf("%d", &N) == 1) {

    // === DEBUGGING ===
    // puts("=====================================");
    // printf("N = %d\n", N);

    // -------------------------------------------------------
    // read input, save slopes & intercepts, save dual points
    rep(i, 0, N-1) {    
      scanf("%lld%lld%lld%lld",&skn[i], &skm[i], &ftn[i], &ftm[i]);
      dual_sk[i] = { skm[i], -skn[i], i };
      dual_ft[i] = { ftm[i], -ftn[i], i };
    }

    // ------------------------------------------
    // get lower/upper hulls for skills/fatigues
    vector<Point> sklh = sk_lower_hull();
    vector<Point> ftuh = ft_upper_hull();


    // === DEBUGGING ===
    // puts("----------");
    // puts("skill lower hull:");
    // for (Point& p : sklh) {
    //   printf("{x = %lld, y = %lld, id = %d, m = %lld, n =%lld}\n", p.x, p.y, p.id, skm[p.id], skn[p.id]);
    // }
    // puts("----------");
    // puts("fatigue upper hull:");
    // for (Point& p : ftuh) {
    //   printf("{x = %lld, y = %lld, id = %d, m = %lld, n =%lld}\n", p.x, p.y, p.id, ftm[p.id], ftn[p.id]);
    // }


    // --------------------------
    // get interval maps
    auto sk_intvmap = get_intervals_map(sklh, skm, skn);
    auto ft_intvmap = get_intervals_map(ftuh, ftm, ftn);


    // === DEBUGGING ===
    // puts("---- sk_intervals -----");
    // for (auto& kv : sk_intvmap) {
    //   double start = kv.first.first.to_double();
    //   double end = kv.first.second.to_double();
    //   printf("\t(%lf, %lf) => [", start, end);
    //   for (int id : kv.second) printf("%d, ", id);
    //   puts("]");
    //   puts("");
    // }

    // puts("---- ft_intervals -----");
    // for (auto& kv : ft_intvmap) {
    //   double start = kv.first.first.to_double();
    //   double end = kv.first.second.to_double();
    //   printf("\t(%lf, %lf) => [", start, end);
    //   for (int id : kv.second) printf("%d, ", id);
    //   puts("]");
    //   puts("");
    // }


    // ------------------------
    // print golden count
    printf("%d\n", count_golden(sk_intvmap, ft_intvmap));
  }
  return 0;
}