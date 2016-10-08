// tags: Point Line Duality, Convex Hull, Fractions

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
bool operator==(const Point& a, const Point& b) {
  return a.x == b.x && a.y == b.y;
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

struct Interval {
  Fraction start;
  Fraction end;
  int id;
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
bool ties[MAXN];

// =======================
// Convex-Hull fuctions
// =======================

ll isLeft(Point& o, Point& a, Point& b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

void remember_ties(Point* pts) {
  rep (i, 1, N-1) {
    Point& a = pts[i-1];
    Point& b = pts[i];
    if (a == b) {
      ties[a.id] = true;
      ties[b.id] = true;
    }
  }
}

/* Get lower hull of skill dual points. This matches skill upper envelope */
vector<Point> sk_lower_hull() {
  // sort dual skill points
  sort(dual_sk, dual_sk + N);
  // remember ties
  remember_ties(dual_sk);
  // build lower hull
  int k = 0;
  vector<Point> lh(N);
  rep(i, 0, N-1) {
    while(k >= 2 && isLeft(lh[k-2], lh[k-1], dual_sk[i]) <= 0) k--;
    lh[k++] = dual_sk[i];
  }
  if (k >= 2 && lh[k-1].x == lh[k-2].x) k--;
  lh.resize(k);
  return lh;
}

/* Get upper hull of fatigue dual points. This matches fatigue lower envelope */
vector<Point> ft_upper_hull() {
  // sort dual fatigue points
  sort(dual_ft, dual_ft + N);
  // remember ties
  remember_ties(dual_ft);
  // build upper hull
  int k = 0;
  vector<Point> uh(N);
  invrep(i, N-1, 0) {
    while(k >= 2 && isLeft(uh[k-2], uh[k-1], dual_ft[i]) <= 0) k--;
    uh[k++] = dual_ft[i];
  }
  if (k >= 2 && uh[k-1].x == uh[k-2].x) k--;
  uh.resize(k);
  return uh;
}

// ==================================

/* Get time intervals from dual points */
vector<Interval> get_intervals(vector<Point>& pts, ll* ms, ll* ns) {

  Fraction prev_t(-INF, 1);
  int prev_id = -1;
  vector<Interval> intvs;

  for (Point& p : pts) {
    if (prev_id != -1) {
      Fraction t (
        ns[p.id] - ns[prev_id],
        ms[prev_id] - ms[p.id]
      );
      if (!ties[prev_id])
        intvs.push_back({prev_t, t, prev_id});
      prev_t = t;      
    }
    prev_id = p.id;
  }
  intvs.push_back({prev_t, Fraction(INF, 1), prev_id});
  return intvs;
}

Fraction TIME_ZERO(0, 1);

/* Count golden athletes by checking intersections between skill intervals
and fatigue intervals. Intervals are swept linearly by shifting 2 pointers. */
int count_golden(
  vector<Interval>& sk_intvs,
  vector<Interval>& ft_intvs) {

  int count = 0;
  int i = 0, j = 0;

  while (i < sk_intvs.size() && j < ft_intvs.size()) {
    Interval& ski = sk_intvs[i];
    Interval& fti = ft_intvs[j];
    Fraction max_start = std::max(ski.start, fti.start);
    Fraction min_end = std::min(ski.end, fti.end);

    if (max_start < min_end && TIME_ZERO < min_end && ski.id == fti.id && !golden[ski.id]) {

      // printf ("golden found!! id = %d\n", ski.id);
      // printf ("\tsk_i: (%lf, %lf)\n", ski.start.to_double(), ski.end.to_double());
      // printf ("\tft_i: (%lf, %lf)\n", fti.start.to_double(), fti.end.to_double());
      // printf ("\tintersection: (%lf, %lf)\n", max_start.to_double(), min_end.to_double());

      golden[ski.id] = true;
      count++;
    }

    if (ski.end < fti.end) ++i;
    else if (fti.end < ski.end) ++j;
    else ++i, ++j;
  }

  return count;
}

int main() {
  while (scanf("%d", &N) == 1) {

    memset(golden, false, sizeof(bool)*N);
    memset(ties, false, sizeof(bool)*N);

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

    // --------------------------
    // get interval maps
    vector<Interval> sk_intvs = get_intervals(sklh, skm, skn);
    vector<Interval> ft_intvs = get_intervals(ftuh, ftm, ftn);

    // ------------------------
    // print golden count
    printf("%d\n", count_golden(sk_intvs, ft_intvs));
  }
  return 0;
}