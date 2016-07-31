// Tags: binary search
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define INF 2000000000.0
typedef long long int ll;

int n;
vector<ll> vel;
vector<ll> pos;

bool collision(double time) {
  double rightmost = -INF;
  FOR(i, 0, n-1)
    if (vel[i] > 0)
      rightmost = max(rightmost, pos[i] + vel[i] * time);
    else
      if (pos[i] + vel[i] * time <= rightmost)
        return true;
  return false;
}

int main() {
  scanf("%d", &n);
  bool lfound = false;
  bool rfound = false;
  ll lstart, rstart, lvel, rvel;

  pos.resize(n);
  vel.resize(n);
  
  FOR(i, 0, n-1) {
    scanf("%I64d %I64d", &pos[i], &vel[i]);
    if (vel[i] > 0) {
      if (!lfound || lstart > pos[i]) {
        lfound = true;
        lstart = pos[i];
        lvel = vel[i];
      }
    } else {
      if (!rfound || rstart < pos[i]) {
        rfound = true;
        rstart = pos[i];
        rvel = vel[i];
      }
    }
  }

  if (lfound && rfound && lstart <= rstart) {
    double tmin = 0;
    double tmax = 0.001 + (double)(rstart - lstart) / (double)(lvel - rvel);
    double tmid;
    int times = 0;
    while (times++ < 80) {
      tmid = (tmin + tmax) * 0.5;
      if (collision(tmid))
        tmax = tmid;
      else
        tmin = tmid;
    }
    printf("%.20lf\n", tmid);
  } else {
    puts("-1");
  }
  return 0;
}