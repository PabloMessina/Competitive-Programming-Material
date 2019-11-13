// TODO: finish this
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
typedef long long int ll;
// -------------------------------
int N;
struct Point {
    ll x, y;
    Point operator-(const Point& p) const { return { x - p.x, y - p.y }; }
    int get_quadrant() const {
        if (x > 0) return y >= 0 ? 0 : 3;
        return y > 0 ? 1 : 2;
    }
    ll cross(const Point& p) const { return x * p.y - y * p.x; }
    ll dot(const Point& p) const { return x * p.x + y * p.y; }
    Point rotate() const { return { -y, x }; }
    bool operator<(const Point& p) const {
        int q = get_quadrant();
        int qp = p.get_quadrant();
        if (q != qp) return q < qp;
        return cross(p) > 0;
    }
};

tuple<ll,ll,ll> hash_line(const Point& p1, const Point& p2) {
    ll a = p1.y - p2.y;
    ll b = p2.x - p1.x;
    ll c = p1.x * (p2.y - p1.y) - p1.y * (p2.x - p1.x);
    ll sgn = (a < 0 or (a == 0 and b < 0)) ? -1 : 1;
    ll g = __gcd(abs(a), __gcd(abs(b), abs(c))) * sgn;
    return make_tuple(a/g, b/g, c/g);
}

bool inconfict[1000][1000];
int ranked_idxs[1000], rank_[1000];
Point pts[1000];
int B[1000];

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N;
    rep(i,0,N-1) {
        cin >> pts[i].x >> pts[i].y >> B[i];
    }
    map<Point, set<tuple<ll,ll,ll>>> slope2lines;
    map<tuple<ll,ll,ll>, uset<int>> line2idxs;
    rep(i,0,N-1) rep(j,0,N-1) {
        if (i == j) continue;
        Point m = pts[j] - pts[i];
        auto line_hash = hash_line(pts[i], pts[j]);
        slope2lines[m].insert(line_hash);
        auto& idxs = line2idxs[line_hash];
        idxs.insert(i);
        idxs.insert(j);
    }
    rep(i,0,N-1) ranked_idxs[i] = i;
    Point dir0 = slope2lines.begin()->first.rotate();
    sort(ranked_idxs, ranked_idxs + N, [&dir0](int i, int j) {
        return dir0.dot(pts[i]) < dir0.dot(pts[j]);
    });
    rep(i,0,N-1) rank_[ranked_idxs[i]] = i;
    int count = 0;
    rep(i,0,N-2) {
        int ii = ranked_idxs[i];
        ll score1 = dir0.dot(pts[ii]);
        rep(j,i+1,N-1) {
            int jj = ranked_idxs[j];
            ll score2 = dir0.dot(pts[jj]);
            assert (score1 <= score2);
            if (score1 < score2 and B[ii] > B[jj]) {
                inconfict[ii][jj] = inconfict[jj][ii] = true;
                count++;
            }
        }
    }
    if (count == 0) {
        cout << "Y\n";
    } else {
        for (auto it = next(slope2lines.begin()); it != slope2lines.end(); ++it) {
            auto prev_it = prev(it);
            auto& prev_lines = prev_it->second;
            auto& cur_lines = it->second;
            Point dir = it->first.rotate();
            auto cmp = [&dir](int i, int j) {
                return dir.dot(pts[i]) < dir.dot(pts[j]);
            };

            for (auto& line_hash : prev_lines) {
                auto& idxs = line2idxs[line_hash];
                int l = INT_MAX;
                int r = INT_MIN;
                for (const int& idx : idxs) {
                    l = min(l, rank_[idx]);
                    r = max(r, rank_[idx]);
                }
                printf("r - l + 1 == %d\n",r-l+1);
                printf("idxs.size() = %d\n",idxs.size());
                assert (r - l + 1 == idxs.size());
                rep(i,l,r) assert (idxs.count(ranked_idxs[i]));
                sort(ranked_idxs + l, ranked_idxs + r + 1, cmp);
                rep(i,l,r-1) {
                    int ii = ranked_idxs[i];
                    ll score1 = dir.dot(pts[ii]);
                    rep(j,i+1,r) {
                        int jj = ranked_idxs[j];
                        ll score2 = dir.dot(pts[jj]);
                        assert (score1 < score2);
                        if (B[ii] < B[jj] and inconfict[ii][jj]) {
                            inconfict[ii][jj] = inconfict[jj][ii] = false;
                            count--;
                        } else if (B[ii] > B[jj] and not inconfict[ii][jj]) {
                            inconfict[ii][jj] = inconfict[jj][ii] = true;
                            count++;
                        }
                    }
                }
            }

            for (auto& line_hash: cur_lines) {
                auto& idxs = line2idxs[line_hash];
                for (auto i = idxs.begin(); i != idxs.end(); ++i) {
                    int ii = *i;
                    for (auto j = next(i); j != idxs.end(); ++j) {
                        int jj = *j;
                        if (inconfict[ii][jj]) {
                            inconfict[ii][jj] = inconfict[jj][ii] = false;
                            count--;
                        }
                    }
                }
            }

            if (count == 0) break;
        }
        if (count) cout << "N\n";
        else cout << "Y\n";
    }
    return 0;
}