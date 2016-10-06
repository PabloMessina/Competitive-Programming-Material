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
  double to_double() {
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
struct Interval {
  Fraction start, end;
  set<int> ids;
};

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

/* DEBUGGING */
void print_interval(Interval& i) {
  printf("\tstart = %lld / %lld = %lf\n", i.start.a, i.start.b, i.start.to_double());
  printf("\tend = %lld / %lld = %lf\n", i.end.a, i.end.b, i.end.to_double());
  printf("\tids = [");
  for (int id : i.ids) printf("%d, ", id);
  puts("]");
}

// ==================================

/* Get intervals by consecutively intersecting original straight lines from their
respective dual points. The intervals can be wide, e.g. (-100, 50) (an open range),
or singleton, e.g. [3,3] (a single dot)*/
vector<Interval> get_intervals(vector<Point>& pts, ll* ms, ll* ns) {
  vector<Interval> intervals;
  Fraction prev_t(-INF, 1);

  int prev_id = -1;
  int curr_id;
  Interval* i_ptr;

  for (Point& p : pts) {
    curr_id = p.id;

    if (prev_id == -1) { // first point
      intervals.push_back(Interval());
      i_ptr = &intervals.back();
      i_ptr->start = prev_t;
      i_ptr->ids.insert(curr_id);

    } else { // next point

      // ref to curr interval
      int k = intervals.size();
      Interval* curr_i = &intervals[k-1];

      if (ms[prev_id] == ms[curr_id]) { // same line
        curr_i->ids.insert(curr_id); // add to the current interval
      } else { // different lines
        // intersection time
        Fraction t(
          ns[curr_id] - ns[prev_id],
          ms[prev_id] - ms[curr_id]
        );
        // close curr interval
        curr_i->end = t;

        if (prev_t < t) { // curr interval is wide          
          // add all id's to previous singleton interval
          if (k >= 2) {
            intervals[k-2].ids.insert(
              curr_i->ids.begin(),
              curr_i->ids.end());
          }

          // add singleton interval
          intervals.push_back(Interval());
          i_ptr = &intervals.back();
          i_ptr->start = t;
          i_ptr->end = t;
          curr_i = &intervals[k-1];
          i_ptr->ids.insert(curr_i->ids.begin(), curr_i->ids.end());

          // open new interval
          intervals.push_back(Interval());
          i_ptr = &intervals.back();
          i_ptr->start = t;
          i_ptr->ids.insert(curr_id);
          // update prev_t
          prev_t = t;
        } else { // curr interval is singleton
          // merge curr singleton interval into previous singleton interval
          intervals[k-2].ids.insert(curr_i->ids.begin(), curr_i->ids.end());
          intervals.pop_back();
          // open new interval
          intervals.push_back(Interval());
          i_ptr = &intervals.back();
          i_ptr->start = t;
          i_ptr->ids.insert(curr_id);
        }
      }
    }
    prev_id = curr_id;
  }
  // close last wide interval
  int k = intervals.size();  
  i_ptr = &intervals[k-1];
  i_ptr->end = {INF, 1};
  if (k >= 2) {
    intervals[k-2].ids.insert(
      i_ptr->ids.begin(), i_ptr->ids.end());
  }
  // return interval list
  return intervals;
}

Fraction TIME_ZERO = { 0, 1 };

/* Get exactly the unique id obtained from intersecting ids1 and ids2,
otherwise return -1 */
int unique_intersection(set<int>& ids1, set<int>& ids2) {
  int count = 0;
  int ans = -1;
  for (int id : ids1) {
    if (ids2.find(id) != ids2.end()) {
      ans = id;
      if (++count > 1)
        return -1;
    }
  }
  return ans;
}

/* Count golden athletes by checking unique intersections between skill intervals
and fatigue intervals. Intervals are swept linearly by shifting 2 pointers. There are 3
kinds of intersections: wide vs wide, wide vs singleton and singleton vs singleton */
int count_golden(vector<Interval>& sk_intervals, vector<Interval>& ft_intervals) {
  memset(golden, 0, sizeof(bool) * N);
  int gcount = 0;

  int i = 0, j = 0;

  while(i < sk_intervals.size() && j < ft_intervals.size()) {
    Interval& sk_i = sk_intervals[i];
    Interval& ft_i = ft_intervals[j];
    bool sk_wide = sk_i.start < sk_i.end;
    bool ft_wide = ft_i.start < ft_i.end;
    bool inters = false;

    if (sk_wide) {
      if (ft_wide) { // wide and wide
        Fraction max_start = std::max(sk_i.start, ft_i.start);
        Fraction min_end = std::min(sk_i.end, ft_i.end);
        if (max_start < min_end && TIME_ZERO < min_end)
          inters = true;
      } else { // wide and sinleton
        Fraction& t = ft_i.start;
        if (TIME_ZERO <= t && sk_i.start < t && t < sk_i.end)
          inters = true;
      }
    } else {
      if (ft_wide) { // sinleton and wide
        Fraction& t = sk_i.start;
        if (TIME_ZERO <= t && ft_i.start < t && t < ft_i.end)
          inters = true;
      } else { // sinleton and sinleton
        if (sk_i.start == ft_i.start)
          inters = true;
      }
    }

    if (inters) {
      int id = unique_intersection(sk_i.ids, ft_i.ids);
      if (id != -1 && !golden[id]) {
        golden[id] = true;
        gcount++;
      }
    }

    if (sk_i.end < ft_i.end) i++;
    else if (ft_i.end < sk_i.end) j++;
    else i++, j++;
  }

  return gcount;
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
    // get intervals
    vector<Interval> sk_intervals = get_intervals(sklh, skm, skn);
    vector<Interval> ft_intervals = get_intervals(ftuh, ftm, ftn);


    // === DEBUGGING ===
    // puts("---- sk_intervals -----");
    // for (Interval& i : sk_intervals) {
    //   puts("-----");
    //   print_interval(i);
    // }

    // puts("---- ft_intervals -----");
    // for (Interval& i : ft_intervals) {
    //   puts("-----");
    //   print_interval(i);
    // }


    // ------------------------
    // print golden count
    printf("%d\n", count_golden(sk_intervals, ft_intervals));
  }
  return 0;
}