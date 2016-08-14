// tags: point in polygon, nonzero rule, winding number
//  and a lot of input handling :)
#include <cstdio>
#include <string>
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
using namespace std;

#define rep(i,a,b) for(int i=a; i<=b; ++i)
#define MAXR 48
#define MAXC 65

typedef vector<int> vi;
typedef pair<int,int> pii;

int R, C, N;
int Rmin, Rmax, Cmin, Cmax;
int r0, c0;
char f;
char arr[MAXR][MAXC];
char arr_aux[MAXR][MAXC];

int shifts[8][2] = {
  {-1, 0},
  {-1, 1},
  {0, 1},
  {1, 1},
  {1, 0},
  {1, -1},
  {0, -1},
  {-1, -1}
};

struct Point { float x, y; };

/* signed area of p0 with respect to (p1 -> p2) */
float isLeft(Point p0, Point p1, Point p2) {
  return (p1.x - p0.x) * (p2.y - p0.y)
    - (p2.x - p0.x) * (p1.y - p0.y);
}

/* check if point is inside polygon using Nonzero Rule */
bool inPolygon(Point p, vector<Point>& pts) {
  int wn = 0;
  Point prev = pts.back();
  rep (i, 0, (int)pts.size() - 1) {
    Point curr = pts[i];
    if (prev.y <= p.y) {
      if (p.y < curr.y && isLeft(p, prev, curr) > 0)
        ++ wn;
    } else {
      if (p.y >= curr.y && isLeft(p, prev, curr) < 0)
        -- wn;
    }
    prev = curr;
  }
  return wn != 0;
}

void processRegion(vi& dirs) {
  int rmin = r0, rmax = r0;
  int cmin = c0, cmax = c0;
  int r = r0, c = c0;

  int first_dir = -1;
  int prev_dir;
  int curr_dir;

  vector<Point> points;
  points.push_back({r0 + 0.5f, c0 + 0.5f});

  queue<pii> final_q;

  for (int dir : dirs) {

    curr_dir = dir;

    r += shifts[dir][0];
    c += shifts[dir][1];

    // sanity checks
    if (r < Rmin || r > Rmax || c < Cmin || c > Cmax) {
      printf("REGION %c GOES OUTSIDE THE ARRAY\n", f);
      return;
    }
    if (arr[r][c] != '.') {
      printf("REGION %c BOUNDARY INTERSECTS REGION %c\n", f, arr[r][c]);
      return;
    }

    // update bounding box
    rmin = min(rmin, r);
    rmax = max(rmax, r);
    cmin = min(cmin, c);
    cmax = max(cmax, c);

    // add to final queue
    final_q.emplace(r, c);
    arr_aux[r][c] = f;

    // add new point / update last point
    // we only add a new point if the direction changes
    // otherwise we simply update the last point
    if (first_dir == -1) {
      first_dir = curr_dir;
      points.push_back({r + 0.5f, c + 0.5f});
    } else {
      if (curr_dir == prev_dir) { // same dir
        points.back() = {r + 0.5f, c + 0.5f}; // update last
      } else { // different dir
        points.push_back({r + 0.5f, c + 0.5f}); // add new one
      }
    }

    // remember prev dir
    prev_dir = curr_dir;
  }

  // check it's closed
  if (r != r0 || c != c0) {
    printf("REGION %c BOUNDARY IS NOT CLOSED\n", f);
    return;
  }

  // special case, if first and last directions are the same
  // we can join first and last edges together
  if (first_dir == curr_dir) {
    points.pop_back();
    points.front() = points.back();
  }
  // remove redundant last point (it's equal to the first one)
  points.pop_back();

  // collect cells within boundary
  rep (r, rmin+1, rmax-1) {
    rep (c, cmin+1, cmax-1) {
      if (arr_aux[r][c] != f && inPolygon({r + 0.5f, c + 0.5f}, points)) {
        // sanity check
        if (arr[r][c] != '.') {
          printf("REGION %c BOUNDARY INTERSECTS REGION %c\n", f, arr[r][c]);
          return;
        }
        final_q.emplace(r, c);
      }
    }
  }

  // after all the sanity checks, fill region's cells
  while (!final_q.empty()) {
    pii u = final_q.front(); final_q.pop();
    arr[u.first][u.second] = f;
  }
}

int main() {
  string line;
  while (true) {

    // read rows, columnss & regions
    getline(cin, line);
    sscanf(line.c_str(), "%d%d%d", &R, &C, &N);
    if (R == 0 || C == 0) break;

    // define working range
    Rmin = 0;
    Rmax = R-1;
    Cmin = 0;
    Cmax = C-1;

    // reset arrays
    memset(arr, '.', sizeof arr);
    memset(arr_aux, '.', sizeof arr_aux);

    // process each region
    while(N--) {

      // read fill char, start row/col, boundary size
      int b;      
      getline(cin, line);
      sscanf(line.c_str(), "%c%d%d%d", &f,&r0,&c0,&b);

      // adjust r0 & c0
      r0--, c0--;

      // read boundary (it may span multiple lines)
      vi dirs;
      while (b) {
        getline(cin, line);
        for (char c : line)
          dirs.push_back(c - 'A');
        b -= line.size();
      }

      // process region
      processRegion(dirs);      
    }

    // print answer
    rep (r, Rmin, Rmax)
      printf("%.*s\n", C, &arr[r][Cmin]);
    puts("");
  }
  return 0;
}