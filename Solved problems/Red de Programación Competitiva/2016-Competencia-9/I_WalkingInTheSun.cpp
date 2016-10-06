#include <bits/stdc++.h>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define invrep(i,a,b) for(int i=a; i>=b; --i)

#define MAXS 50

int S, Q;
double xs[MAXS];
double ys[MAXS];
double rs[MAXS];

int s, t;
double sx, sy, tx, ty;

double dist[MAXS+2];
struct Pair {
  int u;
  double d; 
  bool operator<(const Pair& p) const {
    return d > p.d;
  }
};

inline double dist_p_p(double x1, double y1, double x2, double y2) {
  double dx = x1 - x2;
  double dy = y1 - y2;
  return sqrt(dx*dx + dy*dy);
}

inline double dist_c_c(int i, int j) {
  return max(dist_p_p(xs[i],ys[i],xs[j],ys[j]) - rs[i] - rs[j], 0.0);
}

inline double dist_p_c(double x, double y, int i) {
  return max(dist_p_p(xs[i],ys[i],x,y) - rs[i], 0.0);
}

int main() {
  int T; scanf("%d", &T);
  rep(test, 1, T) {
    scanf("%d", &S);
    rep(i,0,S-1) {
      scanf("%lf%lf%lf",&xs[i],&ys[i],&rs[i]);
    }

    printf("Campus #%d:\n", test);

    // queries
    scanf("%d", &Q);
    rep(q,1,Q) {
      double sx,sy,tx,ty;
      scanf("%lf%lf%lf%lf",&sx,&sy,&tx,&ty);

      // dijkstra
      s = S, t = S+1;
      rep(i,0,S+1) dist[i] = DBL_MAX;
      dist[s] = 0;
      priority_queue<Pair> pq;
      pq.push({s, 0});
      while (!pq.empty()) {
        Pair p = pq.top(); pq.pop();
        if (dist[p.u] < p.d) continue;

        // source
        if (p.u == s) {

          // to circles
          rep(v, 0, S-1) {
            dist[v] = dist_p_c(sx, sy, v);
            pq.push({v, dist[v]});
          }
          // to target
          dist[t] = dist_p_p(sx, sy, tx, ty);

        // shadow
        } else {

          // to circles
          rep(v, 0, S-1) {
            if (v == p.u)
              continue;
            double d = dist[p.u] + dist_c_c(p.u, v);
            if (dist[v] > d) {
              dist[v] = d;
              pq.push({v, d});
            }
          }
          // to target
          double d = dist[p.u] + dist_p_c(tx, ty, p.u);
          if (dist[t] > d) {
            dist[t] = d;
          }
        }
      }

      // answer query
      printf("Path #%d: Shortest sun distance is %.1lf.\n", q, dist[t]);

    }
  }
  return 0;
}