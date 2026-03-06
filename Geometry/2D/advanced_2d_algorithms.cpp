// Find extreme point in Convex Hull
// -----------------------------------
// given two points a and b defining a vector a -> b, and given a convex hull with points
// sorted ccw, find the index in the convex hull of the extreme point.
//  ** the extreme point is the "leftmost" point in the convex hull with respect to the
//     vector a -> b (if there are 2 leftmost points, pick anyone)
int extreme_point_index(P &a, P &b, vector<P> &ch) {
    int n = ch.size();
    P v = b - a;
    v = P(-v.y, v.x); // to find the leftmost point
    if (v*ch[0] >= v*ch[1] && v*ch[0] >= v*ch[n-1]) return 0;
    int l = 0, r = n;
    while (true) {
        int m = (l+r)/2;
        if (v*ch[m] >= v*ch[m+1] && v*ch[m] >= v*ch[m-1]) return m;
        int d1 = v*(ch[l + 1] - ch[l]) > 0;
        int d2 = v*(ch[m + 1] - ch[m]) > 0;
        int a = v*ch[m] > v*ch[l];
        if (d1) { if (d2 && a) l = m; else r = m; }
        else { if (!d2 && a) r = m; else l = m; }
    }
}

// Line Segment and Convex Hull Intersection
pair<int,int> find_crossing_edge(P& a, P& b, vector<P>& ch, int start, int end) {
    int o_ref = turn(a, b, ch[start]);
    int n = ch.size();
    int l = start, r = start + ((end - start + n) % n);
    while (l < r) {
        int m = (l+r) >> 1;
        if (turn(a, b, ch[m % n]) != o_ref) r = m;
        else l = m+1;
    }
    return {(l-1+n) % n, l%n};
}
ll det(P& a, P& b) { return a.x * b.y - a.y * b.x; }
bool find_line_line_intersection(P& a1, P& b1, P& a2, P& b2,
        long double& t1, long double& t2) {
    P d1 = b1 - a1;
    P d2 = b2 - a2;
    P _d2 = d2 * -1;
    ll detA = det(d1, _d2);
    if (detA == 0) return false;
    P b = a2 - a1;
    t1 = (long double)det(b, _d2)/(long double)detA;
    t2 = (long double)det(d1, b)/(long double)detA;
    return true;
}
void find_segment_convexhull_intersection(P& a, P& b, vector<P>& ch) {
    // find rightmost and leftmost points in convex hull wrt vector a -> b
    int i1 = extreme_point_index(a, b, ch);
    int i2 = extreme_point_index(b, a, ch);
    // make sure the extremes are not to the same side
    int t1 = turn(a, b, ch[i1]);
    int t2 = turn(a, b, ch[i2]);
    if (t1 == t2) return; // all points are to the right (left) of a -> b (no intersection)
    // find 2 edges in the convex hull intersected by the straight line <- a - b ->
    pair<int,int> e1 = find_crossing_edge(a, b, ch, i1, i2); // binsearch from i1 to i2 ccw
    pair<int,int> e2 = find_crossing_edge(a, b, ch, i2, i1); // binsearch from i2 to i1 ccw
    // find exact intersection points
    long double r1, s1, r2, s2;
    assert(find_line_line_intersection(a, b, ch[e1.first], ch[e1.second], r1, s1));
    assert(find_line_line_intersection(a, b, ch[e2.first], ch[e2.second], r2, s2));
    // make sure intersections are significant and within line segment range
    if (r1 > 1.0 - EPS and r2 > 1.0 - EPS) return; // intersections above line segment
    if (r1 < EPS and r2 < EPS) return; // intersections below line segment
    if (abs(r1 - r2) < EPS) return; // insignificant intersection in a single point    
    if (r1 > r2) swap(r1, r2), swap(e1, e2), swap(s1, s2); // make sure r1 < r2
    // ** HERE DO WHATEVER YOU WANT WITH INTERSECTIONS FOUND
    //   1) a + (b-a) * max(r1, 0)  <--- first point of segment a -> b inside convex hull
    //      if r1 < 0, point a is strictly inside the convex hull
    //   2) a + (b-a) * min(r2, 1)  <--- last point of segment a -> b inside convex hull
    //      if r2 > 1, point b is strictly inside the convex hull
    cout << "(significant) intersection detected!\n";
}

// Check if at least one pair of segments intersect among many
// ----------------------------------------------------------
// given a list of segments, check if at least one pair of segments intersect
// in O(N log N) time complexity with a sweep line algorithm
enum EventType { START, END };
struct Event {
    P p; // point of the event
    EventType type; // type of the event
    int id; // id of the segment
    Event(P p, EventType type, int id) : p(p), type(type), id(id) {}
    bool operator<(const Event& e) const {
        if (abs(p.x - e.p.x) > EPS) return p.x < e.p.x;
        return type < e.type;
    }
};
// Custom comparator for sorting segments
long double current_x; // current x coordinate for the sweep line
long double get_y(P& p1, P& p2, long double x) { // get y coordinate of a point on the segment
    if (p1.x == p2.x) return min(p1.y, p2.y); // vertical segment
    return p1.y + (p2.y - p1.y) * (x - p1.x) / (p2.x - p1.x);
}
struct is_below {
    vector<Segment>& segments;
    is_below(vector<Segment>& segments) : segments(segments) {}
    bool operator()(int i, int j) const {
        Segment& si = segments[i];
        Segment& sj = segments[j];
        long double y1 = get_y(si.p1, si.p2, current_x);
        long double y2 = get_y(sj.p1, sj.p2, current_x);
        if (abs(y1 - y2) > EPS) return y1 < y2;
        return i < j; // if same y, sort by id to avoid collisions
    }
};
bool do_segments_intersect(int i, int j, vector<Segment>& segments) {
    Segment& si = segments[i];
    Segment& sj = segments[j];
    return do_segments_intersect(si.p1, si.p2, sj.p1, sj.p2);
}
bool do_at_least_one_pair_of_segments_intersect(vector<Segment>& segments) {    
    // Create events for each segment
    int n = segments.size();
    vector<Event> events;
    rep(i,0,n) {
        Segment& s = segments[i];
        if (s.p1.x > s.p2.x) swap(s.p1, s.p2);
        events.eb(s.p1, START, i);
        events.eb(s.p2, END, i);
    }
    sort(events.begin(), events.end());
    // Run sweep line
    multiset<int, is_below> active_segments = multiset<int, is_below>(is_below(segments));
    vector<set<int, is_below>::iterator> active_segments_it(n);
    for (auto& e : events) {
        current_x = e.p.x;
        Segment& cur_s = segments[e.id];
        if (e.type == START) {
            auto it = active_segments.insert(e.id);
            active_segments_it[e.id] = it;
            if (it != active_segments.begin()) {
                auto prev = std::prev(it);
                if (do_segments_intersect(e.id, *prev, segments)) return true;
            }
            auto next = std::next(it);
            if (next != active_segments.end()) {
                if (do_segments_intersect(e.id, *next, segments)) return true;
            }
        } else {
            auto it = active_segments_it[e.id];
            assert(it != active_segments.end());
            if (it != active_segments.begin() && std::next(it) != active_segments.end()) {
                auto prev = std::prev(it);
                auto next = std::next(it);
                if (do_segments_intersect(*prev, *next, segments)) return true;
            }
            active_segments.erase(it);
        }
    }
    return false;
}