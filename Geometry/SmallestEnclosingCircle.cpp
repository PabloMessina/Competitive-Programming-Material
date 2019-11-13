#define rep(i,a,b) for(int i=a; i < b; ++i)
// find the smallest circle enclosing a list of points using Welzl’s randomized algorithm
// O(N) expected time
// references: https://www.cse.iitk.ac.in/users/ssahai/talks/sec.pdf
// https://www.nayuki.io/res/smallest-enclosing-circle/computational-geometry-lecture-6.pdf
void smallest_enclosing_circle(vector<Point>& pts, Point& center, double& r) {
    random_shuffle(pts.begin(), pts.end());
    center = pts[0]; r = 0;
    int N = pts.size();
    rep(i,1,N) {
        if ((pts[i] - center).norm() > r + EPS) {
            center = pts[i];
            r = 0;
            rep(j,0,i) {
                if ((pts[j] - center).norm() > r + EPS) {
                    center = (pts[i] + pts[j]) * 0.5;
                    r = (pts[i] - center).norm();
                    rep(k,0,j) {
                        if ((pts[k] - center).norm() > r + EPS) {
                            center = circumcenter(pts[i], pts[j], pts[k]);
                            r = (pts[k] - center).norm();
                        }
                    }
                }
            }
        }
    }
}