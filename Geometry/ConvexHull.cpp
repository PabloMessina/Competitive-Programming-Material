// Andrew's Montone Chain Algorithm
struct Point {
  double x, y;
  bool operator<(const Point& p) {
    return x < p.x || (x == p.x && y < p.y);
  }
};

double isLeft(Point o, Point a, Point b) {
  return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

vector<Point> upper_hull(vector<Point>& P) {
  // sort points lexicographically
  int n = P.size(), k = 0;
  sort(P.begin(), P.end());

  // build upper hull
  vector<Point> uh(n);
  invrep (i, n-1, 0) {
    while (k >= 2 && isLeft(uh[k-2], uh[k-1], P[i]) <= 0) k--;
    uh[k++] = P[i];
  }
  uh.resize(k);
  return uh;
}

vector<Point> lower_hull(vector<Point>& P) {
  // sort points lexicographically
  int n = P.size(), k = 0;
  sort(P.begin(), P.end());

  // collect lower hull
  vector<Point> lh(n);
  rep (i, 0, n-1) {
    while (k >= 2 && isLeft(lh[k-2], lh[k-1], P[i]) <= 0) k--;
    lh[k++] = P[i];
  }
  lh.resize(k);
  return lh;
}

vector<Point> convex_hull(vector<Point>& P) {
  int n = P.size(), k = 0;

  // set initial capacity
  vector<Point> H(2*n);

  // Sort points lexicographically
  sort(P.begin(), P.end());

  // Build lower hull
  for (int i = 0; i < n; ++i) {
    while (k >= 2 && isLeft(H[k-2], H[k-1], P[i]) <= 0) k--;
    H[k++] = P[i];
  }

  // Build upper hull
  for (int i = n-2, t = k+1; i >= 0; i--) {
    while (k >= t && isLeft(H[k-2], H[k-1], P[i]) <= 0) k--;
    H[k++] = P[i];
  }

  // remove extra space
  H.resize(k-1);
  return H;
}