// GIVES WRONG ANSWER
#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define INF 100000000

typedef long long int ll;

int V;
struct Segment { ll miny, maxy; };
map<ll, Segment> dict;
vector<ll> maxy_from;
vector<ll> miny_from;
ll gmaxy, gminy, gmaxx, gminx;

void update_segment(ll x, ll y) {
  auto it = dict.find(x);
  if (it == dict.end()) {
    dict[x] = {y, y};
  } else {
    Segment& s = it->second;
    s.miny = min(y, s.miny);
    s.maxy = max(y, s.maxy);
  }
}

void update_globals(ll x, ll y) {
  gmaxx = max(gmaxx, x);
  gminx = min(gminx, x);
  gmaxy = max(gmaxy, y);
  gminy = min(gminy, y);
}

int main() {
  while (scanf("%d", &V) == 1) {

    dict.clear();
    gmaxx = 0, gmaxy = 0, gminx = INF, gminy = INF;

    rep(i,0,V-1) {
      ll x,y; scanf("%lld%lld",&x,&y);
      update_segment(x-1,y-1);
      update_segment(x-1,y+1);
      update_segment(x+1,y-1);
      update_segment(x+1,y+1);

      update_globals(x-1,y-1);
      update_globals(x-1,y+1);
      update_globals(x+1,y-1);
      update_globals(x+1,y+1);
    }

    int n = dict.size();
    maxy_from.resize(n);
    miny_from.resize(n);
    int i = n-1;

    for (auto it = dict.rbegin(); it != dict.rend(); ++it) {
      Segment& s = it->second;
      if (i == n-1) {
        maxy_from[i] = s.maxy;
        miny_from[i] = s.miny;
      } else {        
        maxy_from[i] = max(maxy_from[i+1], s.maxy);
        miny_from[i] = min(miny_from[i+1], s.miny);
      }
      --i;
    }

    ll A = 0;
    ll top, bottom;
    ll next_top, next_bottom;
    ll prev_x, prev_miny, prev_maxy;
    i = 0;

    for (auto& it : dict) {
      ll x = it.first;
      Segment& s = it.second;

      if (i == 0) { // first vertical segment

        top = s.maxy;
        bottom = s.miny;

      } else { // non-first vertical segment

        if (s.maxy > top && s.miny < bottom) {
          A += (x - prev_x) * (top - bottom);
          top = s.maxy;
          bottom = s.miny;
        } else if (s.maxy > top && s.miny >= bottom) {
          if (s.miny == miny_from[i]) {
            if (s.miny >= top) {
              A += s.miny - top + 1;
              A += x - prev_x;
              top = s.maxy;
              bottom = s.miny;
            } else {
              A += (top - s.miny) * (x - prev_x);
              top = s.maxy;
              bottom = s.miny;
            }
          } else {
            A += (top - bottom) * (x - prev_x);
            top = s.maxy;
          }
        } else if (s.maxy <= top && s.miny < bottom) {
          if (s.maxy == maxy_from[i]) {
            if (s.maxy <= bottom) {
              A += bottom - s.maxy + 1;
              A += x - prev_x;
              top = s.maxy;
              bottom = s.miny;
            } else {
              A += (s.maxy - bottom) * (x - prev_x);
              top = s.maxy;
              bottom = s.miny;
            }
          } else {
            A += (top - s.miny) * (x - prev_x);
            bottom = s.miny;
          }
        } else { // s.maxy <= top && s.miny >= bottom

          if (s.maxy == maxy_from[i]) top = s.maxy;
          if (s.miny == miny_from[i]) bottom = s.miny;
          A += (top - bottom) * (x - prev_x);
        }

      }

      printf("i = %d, top=%lld, bottom=%lld, x = %lld, A=%lld\n", i, top, bottom, x, A);

      prev_x = x;
      ++i;
    }

    ll P = 2 * (gmaxx - gminx + gmaxy - gminy);
    printf("%lld %lld\n", P, A);

  }
  return 0;
}