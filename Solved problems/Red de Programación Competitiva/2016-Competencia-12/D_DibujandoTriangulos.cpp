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

ll intsqrt(ll x) {
  ll y0 = x;
  while (true) {
    ll y1 = (y0 + x / y0) / 2;
    if (y1 == y0) break;
    y0 = y1;
  }
  return y0;
}

bool perfect_square(ll x, ll& root) {
  root = intsqrt(x);
  return root * root == x;
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
    // printf("\t\t ******** ######### t = (%d,%d,%d)\n",i,j,it->id);
  }
}

void find_similars(int i, int j, ll ta2, ll tb2, ll tc2) {
  // puts("");
  // puts("----------------------");
  // printf("==> find_similars(i=%d, j=%d)\n",i,j);

  // printf("\ttriangles (before) = %d\n", triangles.size());

  ll dij2 = square_dist(i,j);
  ll aux1 = (tb2 * dij2) % ta2;
  ll aux2 = (tc2 * dij2) % ta2;
  Point& pi = P[i], pj = P[j];

  // printf("\t ta2 = %lld, tb2 = %lld, tc2 = %lld, dij2 = %lld\n",ta2,tb2,tc2,dij2);
  // printf("\t aux1 = %lld, aux2 = %lld\n",aux1, aux2);
  // printf("pi = (x: %lld, y: %lld)\n", pi.x, pi.y);
  // printf("pj = (x: %lld, y: %lld)\n", pj.x, pj.y);

  if (aux1 != 0 || aux2 != 0)
    return;

  ll ri_2 = tc2 * dij2 / ta2;
  ll rj_2 = tb2 * dij2 / ta2;

  ll A = 2*(pi.x - pj.x);
  ll B = 2*(pi.y - pj.y);
  ll C = (ri_2 - rj_2 + pj.x*pj.x - pi.x*pi.x + pj.y*pj.y - pi.y*pi.y);

  // printf("\t ri_2=%lld, rj_2=%lld\n",ri_2,rj_2);
  // printf("\t A=%lld, B=%lld, C=%lld\n",A,B,C);

  queue<Point> pts;

  if (A == 0) {
    // puts("\t** A == 0");

    if (C % B != 0)
      return;    

    ll y = -C / B;
    ll disc = ri_2 -  (y - pi.y)*(y - pi.y);
    if (disc < 0)
      return;

    ll root;
    if (!perfect_square(disc, root))
      return;

    ll x1 = -root + pi.x;
    ll x2 = root + pi.x;

    // printf("\t   y = %lld\n", y);
    // printf("\t   disc = %lld\n", disc);
    // printf("\t   root = %lld\n", root);
    // printf("\t   x1 = %lld\n", x1);
    // printf("\t   x2 = %lld\n", x2);
    
    try_add_similar(i,j,x1,y);
    try_add_similar(i,j,x2,y);

  } else if (B == 0) {
    // puts("B == 0");
    if (C % A != 0)
      return;

    ll x = -C/A;
    ll disc = ri_2 - (x - pi.x) * (x - pi.x);
    if (disc < 0)
      return;

    ll root;
    if (!perfect_square(disc, root));
      return;

    ll y1 = -root + pi.y;
    ll y2 = root + pi.y;

    try_add_similar(i,j,x,y1);
    try_add_similar(i,j,x,y2);

  } else {
    // puts("A != 0 and B != 0");

    ll cby = C + B*pi.y;
    ll B2 = B*B;

    ll a = B2 + A*A;
    ll b = -2*pi.x*B2 + 2*A*cby;
    ll c = B2*(pi.x*pi.x - ri_2) + cby*cby;
    ll disc = b*b - 4*a*c;

    // printf("\t a=%lld, b=%lld, c=%lld, disc=%lld\n",a,b,c,disc);


    if (disc < 0)
      return;

    ll root;    
    if (!perfect_square(disc, root))
      return;

    // printf("\t root=%lld\n", root);

    ll num, den, x, y;    
    den = 2*a;

    // sol 1
    num = -b - root;
    if (num % den == 0) {
      x = num / den;
      num = -C - A*x;
      if (num % B == 0) {
        y = num / B;
        try_add_similar(i,j,x,y);
      }
    }

    // sol 2
    num = -b + root;
    if (num % den == 0) {
      x = num / den;
      num = -C - A*x;
      if (num % B == 0) {
        y = num / B;
        try_add_similar(i,j,x,y);
      }
    }
  }

  // printf("\ttriangles (after) = %d\n", triangles.size());
}

int main() {
  scanf("%d", &N);
  P.resize(N);
  rep(i,0,N-1) {
    scanf("%lld%lld", &P[i].x, &P[i].y);
    P[i].id = i;
    Pset.insert(P[i]);

    // printf("P[i=%d] = (%lld, %lld)\n", i, P[i].x, P[i].y);
  }

  ll ta2 = square_dist(0,1);
  ll tb2 = square_dist(1,2);
  ll tc2 = square_dist(2,0);

  // printf("ta2(0,1) = %lld\n", ta2);
  // printf("tb2(1,2) = %lld\n", tb2);
  // printf("tc2(2,0) = %lld\n", tc2);

  rep(i, 0, N-1) rep(j, 0, N-1)
    if (i != j)
      find_similars(i, j, ta2, tb2, tc2);

  // puts("============");
  // puts("triangles:");
  // for (auto& t : triangles) {
  //   printf("(%d,%d,%d)\n", std::get<0>(t), std::get<1>(t), std::get<2>(t));
  // }

  printf("%d\n", triangles.size());

  return 0;
}