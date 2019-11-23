// tags: geometry, area of union of rectangles, green's theorem,
// sweep line, galloping search, binary search, and a lot of implementation ...
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define umap unordered_map
typedef long long int ll;
// -------------------------------
int N, M, P;
struct Point {
    ll x, y;
};
struct Segment {
    Point a, b;
};
struct Rectangle {
    Point a, b;
    void clip(ll xmin, ll xmax, ll ymin, ll ymax) {
        a.x = min(max(xmin, a.x), xmax);
        b.x = min(max(xmin, b.x), xmax);
        a.y = min(max(ymin, a.y), ymax);
        b.y = min(max(ymin, b.y), ymax);
    }
    Rectangle() {}
    Rectangle(Point& c, ll r, bool apply_clipping = true) {
        a = { c.x - r, c.y - r };
        b = { c.x + r, c.y + r };
        if (apply_clipping) clip(1, 2*M+1, 1, 2*N+1);
    }
    Segment get_up_segment() {
        return { {b.x, a.y}, b };
    }
    Segment get_down_segment() {
        return { {a.x, b.y}, a };
    }
};
Point plants[20];
Rectangle rects[20];

bool between_strict(ll x, ll a, ll b) { return a < x and x < b; }

ll get_union_area(ll rad) {
    rep(i,0,P) rects[i] = Rectangle(plants[i], rad);
    ll area = 0;
    rep(i,0,P) {
        vector<pair<ll, ll>> up_pairs, down_pairs;
        Segment up = rects[i].get_up_segment();
        Segment down = rects[i].get_down_segment();
        rep(j,0,P) {
            if (i == j) continue;
            Rectangle& rec = rects[j];
            // up
            if (between_strict(up.a.x, rec.a.x, rec.b.x) or
                    (up.a.x == rec.b.x and i < j)) {
                ll ymin = max(up.a.y, rec.a.y);
                ll ymax = min(up.b.y, rec.b.y);
                if (ymin < ymax) {
                    up_pairs.emplace_back(ymin, ymax);
                }
            }
            // down
            if (between_strict(down.a.x, rec.a.x, rec.b.x) or
                    (down.a.x == rec.a.x and i < j)) {
                ll ymax = min(down.a.y, rec.b.y);
                ll ymin = max(down.b.y, rec.a.y);
                if (ymin < ymax) {
                    down_pairs.emplace_back(ymin, ymax);
                }
            }
        }
        // up contribution
        ll cont = 0;
        ll y = up.a.y;
        sort(up_pairs.begin(), up_pairs.end());
        for (auto& i : up_pairs) {
            if (y < i.first) cont += i.first - y;
            y = max(y, i.second);
        }
        cont += up.b.y - y;
        area += cont * up.a.x;
        // down contribution
        cont = 0;
        y = down.b.y;
        sort(down_pairs.begin(), down_pairs.end());
        for (auto& i : down_pairs) {
            if (y < i.first) cont += i.first - y;
            y = max(y, i.second);
        }
        cont += down.a.y - y;
        area -= cont * down.a.x;
    }
    return area;
}

vector<tuple<ll,ll,ll>> get_compact_segments(umap<ll,vector<pair<ll,ll>>>& segs_dict) {
    vector<tuple<ll,ll,ll>> comp_segs;
    for (auto& kv : segs_dict) {
        auto& segs = kv.second;
        sort(segs.begin(), segs.end());
        auto tmp = segs[0];
        rep(i,1,segs.size()) {
            if (tmp.second >= segs[i].first) {
                tmp.second = max(tmp.second, segs[i].second);
            } else {
                comp_segs.emplace_back(kv.first, tmp.first, tmp.second);
                tmp = segs[i];
            }
        }
        comp_segs.emplace_back(kv.first, tmp.first, tmp.second);
    }
    return comp_segs;
}

vector<Point> get_intersection_points(
        vector<tuple<ll,ll,ll>>& h_segs, vector<tuple<ll,ll,ll>>& v_segs) {
    vector<Point> pts;
    for (auto& hseg : h_segs) {
        ll y,x1,x2; tie(y,x1,x2) = hseg;
        for (auto& vseg : v_segs) {
            ll x,y1,y2; tie(x,y1,y2) = vseg;
            if (x1 <= x and x <= x2 and y1 <= y and y <= y2) {
                pts.push_back({x, y});
            }
        }
    }
    return pts;
}

ll count_pts_up(ll y_ref, vector<tuple<ll,ll,ll>>& hsegs, vector<tuple<ll,ll,ll>>& vsegs,
        vector<Point>& intersec_pts) {
    ll count = 0;
    for (auto& seg : hsegs) {
        ll y, x1, x2; tie(y, x1, x2) = seg;
        if (y >= y_ref) count += (x2 - x1)/2 + 1;
    }
    for (auto& seg : vsegs) {
        ll x, y1, y2; tie(x, y1, y2) = seg;
        if (y1 >= y_ref) count += (y2 - y1)/2 + 1;
        else if (y2 >= y_ref) count += (y2 - y_ref)/2 + 1;
    }
    for (auto& pt : intersec_pts) {
        if (pt.y >= y_ref) count--;
    }
    return count;
}

ll count_pts_left(ll x_ref, ll y_ref, vector<tuple<ll,ll,ll>>& hsegs, vector<tuple<ll,ll,ll>>& vsegs,
        vector<Point>& intersec_pts) {
    ll count = 0;
    for (auto& seg : hsegs) {
        ll y, x1, x2; tie(y, x1, x2) = seg;
        if (y != y_ref) continue;
        if (x1 <= x_ref) count += (min(x_ref, x2) - x1)/2 + 1;
    }
    for (auto& seg : vsegs) {
        ll x, y1, y2; tie(x, y1, y2) = seg;
        if (x <= x_ref and y1 <= y_ref and y_ref <= y2) count++;
    }
    for (auto& pt : intersec_pts) {
        if (pt.y == y_ref and pt.x <= x_ref) count--;
    }
    return count;
}

umap<ll, vector<pair<ll,ll>>> get_horizontal_segments(ll rad) {
    rep(i,0,P) rects[i] = Rectangle(plants[i], rad, false);
    umap<ll, vector<pair<ll,ll>>> hsegs;
    vector<pair<ll,ll>> pairs;    
    rep(i,0,P) {
        Rectangle rec(plants[i], rad, false);
        rec.clip(2, 2*M, 2, 2*N);
        ll x1 = rec.a.x;
        ll x2 = rec.b.x;
        for (ll y : { rec.a.y, rec.b.y }) { // up and down
            if (abs(y - plants[i].y) == rad) {
                pairs.clear();
                rep(j,0,P) {
                    if (i == j) continue;
                    if (between_strict(y, rects[j].a.y, rects[j].b.y)) {
                        ll xs = max(x1, rects[j].a.x);
                        ll xe = min(x2, rects[j].b.x);
                        if (xs < xe) pairs.emplace_back(rects[j].a.x, rects[j].b.x);
                    }
                }
                sort(pairs.begin(), pairs.end());
                ll last_x = x1;
                for (auto& p : pairs) {
                    if (p.first >= last_x) {
                        hsegs[y].emplace_back(last_x, p.first);
                    }
                    last_x = max(last_x, p.second);
                }
                if (last_x <= x2) hsegs[y].emplace_back(last_x, x2);
            }
        }        
    }
    return hsegs;
}

umap<ll, vector<pair<ll,ll>>> get_vertical_segments(ll rad) {
    rep(i,0,P) rects[i] = Rectangle(plants[i], rad, false);
    umap<ll, vector<pair<ll,ll>>> vsegs;
    vector<pair<ll,ll>> pairs;    
    rep(i,0,P) {
        Rectangle rec(plants[i], rad, false);
        rec.clip(2, 2*M, 2, 2*N);
        ll y1 = rec.a.y;
        ll y2 = rec.b.y;
        for (ll x : { rec.a.x, rec.b.x }) { // left and right
            if (abs(x - plants[i].x) == rad) {
                pairs.clear();
                rep(j,0,P) {
                    if (i == j) continue;
                    if (between_strict(x, rects[j].a.x, rects[j].b.x)) {
                        ll ys = max(y1, rects[j].a.y);
                        ll ye = min(y2, rects[j].b.y);
                        if (ys < ye) pairs.emplace_back(rects[j].a.y, rects[j].b.y);
                    }
                }
                sort(pairs.begin(), pairs.end());
                ll last_y = y1;
                for (auto& p : pairs) {
                    if (p.first >= last_y) {
                        vsegs[x].emplace_back(last_y, p.first);
                    }
                    last_y = max(last_y, p.second);
                }
                if (last_y <= y2) vsegs[x].emplace_back(last_y, y2);
            }
        }        
    }
    return vsegs;
}

Point get_position(ll p) {
    // find radius
    ll rad_max = 3;
    while (1) {
        ll area = get_union_area(rad_max) >> 2;
        if (area - P >= p) break;
        rad_max = rad_max * 2 + 1;
    }
    ll rad;
    if (rad_max == 3) {
        rad = rad_max;
    } else {
        ll l = (((rad_max-1)>>1)-1)>>1;
        ll r = (rad_max-1)>>1;
        while (l < r) {
            ll m = (l+r)>>1;
            ll area = get_union_area(2*m+1) >> 2;
            if (area - P >= p) r = m;
            else l = m+1;
        }
        rad = 2*l+1;
    }
    ll area_bef = get_union_area(rad - 2) >> 2;
    p -= (area_bef - P);    
    auto h_segs = get_horizontal_segments(rad - 1);
    auto v_segs = get_vertical_segments(rad - 1);
    auto h_comp_segs = get_compact_segments(h_segs);
    auto v_comp_segs = get_compact_segments(v_segs);
    auto intersec_pts = get_intersection_points(h_comp_segs, v_comp_segs);
    
    // find y coordinate
    ll l = 1, r = N;
    while (l < r) {
        ll m = (l+r)>>1;
        if (count_pts_up(2*(N-m+1), h_comp_segs, v_comp_segs, intersec_pts) >= p) {
            r = m;
        } else {
            l = m+1;
        }
    }
    ll y = 2*(N-l+1);    
    p -= count_pts_up(y+2, h_comp_segs, v_comp_segs, intersec_pts);

    // find x coordinate
    l = 1, r = M;
    while (l < r) {
        ll m = (l+r)>>1;
        if (count_pts_left(2*m, y, h_comp_segs, v_comp_segs, intersec_pts) >= p) {
            r = m;
        } else {
            l = m+1;
        }
    }
    ll x = 2*l;
    return {x, y};
}

int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N >> M >> P and N) {
        rep(i,0,P) {
            ll x, y; cin >> y >> x;
            plants[i] = {2*x, 2*(N-y+1)};
        }
        int Q; cin >> Q;
        while (Q--) {
            ll p; cin >> p;
            Point pos = get_position(p);
            ll row = N - (pos.y/2) + 1;
            ll col = pos.x/2;
            cout << row << ' ' << col << '\n';
        }
        cout << "-\n";
    }
    return 0;
}