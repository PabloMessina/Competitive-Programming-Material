// tags: cosine theorem, trigonometry, integer equations
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)

typedef tuple<int,int,int> iii;
typedef int long long ll;

struct Point {
  ll x, y; int id; 
  Point() {}
  Point(ll x, ll y) {
    this->x = x;
    this->y = y;
    this->id = -1;
  }
};
bool operator<(const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

int N;
vector<Point> P;
set<Point> Pset;
set<iii> triangles;

ll square_dist(int i, int j) {
  ll dx = P[i].x - P[j].x;
  ll dy = P[i].y - P[j].y;
  return dx*dx + dy*dy;
}

bool perfect_square(ll x, ll& root) {
  if (x < 0) return false;
  root = (ll)sqrt(x);
  return (root * root == x || ++root * root == x);
}

iii get_triple(int a, int b, int c) {
  int aa = min(min(a,b),c);
  int cc = max(max(a,b),c);
  int bb = a + b + c - aa - cc;
  return iii(aa, bb, cc);
}

void try_add_similar(int i, int j, ll x, ll y) {
  auto it = Pset.find(Point(x,y));
  if (it != Pset.end()) {    
    triangles.insert(get_triple(i, j, it->id));
  }
}

void find_similar(int i, int j, ll ta2, ll tb2, ll tc2) {

  ll a2 = square_dist(i, j);
  if (((tb2 * a2) % ta2 != 0) || ((tc2 * a2) % ta2 != 0))
    return;

  ll b2 = (tb2 * a2) / ta2;
  ll c2 = (tc2 * a2) / ta2;

  ll aux = a2+b2-c2;
  ll disc = 4*a2*b2-aux*aux;

  ll root;
  if (!perfect_square(disc, root))
    return;

  ll x1 = P[i].x, y1 = P[i].y;
  ll x2 = P[j].x, y2 = P[j].y;
  ll x, y;
  ll num, den;
  den = 2*a2;

  num = aux * (x2-x1) - root * (y2-y1);
  if (num % den != 0)
    return;
  x = x1 + num / den;

  num = aux * (y2-y1) + root * (x2-x1);
  if (num % den != 0)
    return;
  y = y1 + num / den;

  try_add_similar(i, j, x, y);
}

int main() {
  scanf("%d", &N);
  P.resize(N);
  rep(i,0,N-1) {
    scanf("%lld%lld", &P[i].x, &P[i].y);
    P[i].id = i;
    Pset.insert(P[i]);
  }

  ll ta2 = square_dist(0,1);
  ll tb2 = square_dist(1,2);
  ll tc2 = square_dist(2,0);

  rep(i, 0, N-1) rep(j, 0, N-1)
    if (i != j) {
      find_similar(i, j, ta2, tb2, tc2);
      find_similar(i, j, ta2, tc2, tb2);
    }

  printf("%d\n", (int)triangles.size());

  return 0;
}