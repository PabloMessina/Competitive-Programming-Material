// NOTE: this solution is too slow for the largest test case (it takes around 20 seconds to run).

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------

const double PI = acos(-1);
const double EPS = 1e-12;

typedef long long int T;
struct P { // 2D
    T x, y;
    P() {}
    P(T x, T y) : x(x), y(y) {}
    bool operator==(const P& p) const { return x==p.x && y == p.y; }
    P operator+(const P& p) const { return {x+p.x, y+p.y}; }
    P operator-(const P& p) const { return {x-p.x, y-p.y}; }
    P operator*(T d) const { return {x*d, y*d}; }
    P operator/(T d) const { return {x/d, y/d}; }
    T operator^(const P& p) const { return x*p.y - y*p.x; } // cross product
    T operator*(const P& p) const { return x*p.x + y*p.y; } // dot product
    P neg() { return { -x, -y }; }
    P rot_ccw() { return { -y, x }; }
    P rot_cw() { return { y, -x }; }
    T norm2() { return x*x + y*y; }
    double norm() { return sqrt(norm2()); }
    int quad() const { return (x >= 0) ? (y >= 0 ? 0: 3) : (y >= 0 ? 1 : 2); } // 0, 1, 2, 3        
    double angle() { return atan2(y, x); } // [-PI, PI] 
    P unit() { return (*this)/norm(); }
    bool operator<(const P& p) const { // smaller quadrant or same quadrant and to the right
        int q = quad(), qp = p.quad();
        return q != qp ? q < qp : ((*this)^p) > 0;
    }
    bool same_angle(const P& p) { // two vectors pointing to the same direction
        return quad() == p.quad() and ((*this)^p) == 0;
    }
};

struct Triangle {
    P a, b, c;
    Triangle(P a, P b, P c) : a(a), b(b), c(c) {}
    T area() {
        return abs((b-a)^(c-a));
    }
};

ll signed_area(vector<P>& p) {
    int n = p.size(); ll a = 0;
    rep(i,0,n) { int j = (i+1) % n; a += (p[i].x + p[j].x) * (p[j].y - p[i].y); }
    return a;
}

int n;
vector<Triangle> triangles;
vector<P> border;

void dijkstra(int s, int n, vector<vector<pair<int, double>>>& g, vector<double>& D, vector<int>& P) {
    P.assign(n, -1);
    D.assign(n, DBL_MAX);
    D[s] = 0;
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q; // minheap
    q.emplace(0, s);
    while (q.size()) {
        double d; int u; tie(d, u) = q.top(); q.pop(); // u = node, d = mindist from s to u
        if (D[u] < d) continue; // skip outdated improvements
        for (auto& e : g[u]) {
            if (D[e.ff] > d + e.ss) {
                D[e.ff] = d + e.ss;
                P[e.ff] = u;
                q.emplace(D[e.ff], e.ff);
            }
        }
    }
}

// void save_graph_to_txt(vector<vector<pair<int, double>>>& g,
//                     vector<int>& pointId2borderIndex,
//                     vector<P>& border,
//                     P& p_start, P& p_end,
//                     string filename = "graph.txt") {
//     set<tuple<int,int,int,int>> edges;
//     rep(u,0,g.size()) for (auto& e : g[u]) {
//         int v = e.ff;
//         P pu = border[pointId2borderIndex[u]];
//         P pv = border[pointId2borderIndex[v]];
//         if (pu.x > pv.x) swap(u, v);
//         else if (pu.x == pv.x and pu.y > pv.y) swap(u, v);
//         edges.emplace(u, v, pu.x, pu.y);
//     }

//     ofstream file(filename);
//     // save root
//     file << p_start.x << " " << p_start.y << "\n";
//     // save target
//     file << p_end.x << " " << p_end.y << "\n";
//     // save edges
//     for (auto& e : edges) {
//         int u, v, x, y; tie(u, v, x, y) = e;
//         file << x << " " << y << " " << border[pointId2borderIndex[v]].x << " " << border[pointId2borderIndex[v]].y << "\n";
//     }
//     file.close();
// }

// // Custom hash function for tuples
// struct TupleHash {
//     template <typename T>
//     std::size_t operator()(const T& t) const {
//         std::size_t hash = 0;
//         std::hash<typename std::tuple_element<0, T>::type> hasher;
//         for (size_t i = 0; i < std::tuple_size<T>::value; ++i) {
//             hash ^= hasher(std::get<i>(t)) + 0x9e3779b9 + (hash << 6) + (hash >> 2);
//         }
//         return hash;
//     }
// };

// Custom hash function for tuples
struct TupleHash {
    template <typename Tuple, std::size_t... Indices>
    std::size_t hash_impl(const Tuple& t, std::index_sequence<Indices...>) const {
        std::size_t hash = 0;
        // Combine hashes of each tuple element using XOR and a seed
        ((hash ^= std::hash<std::tuple_element_t<Indices, Tuple>>{}(std::get<Indices>(t)) + 0x9e3779b9 + (hash << 6) + (hash >> 2)), ...);
        return hash;
    }

    template <typename Tuple>
    std::size_t operator()(const Tuple& t) const {
        // Use std::index_sequence to apply hash_impl with indices for each element in the tuple
        return hash_impl(t, std::make_index_sequence<std::tuple_size<Tuple>::value>{});
    }
};

// Custom hash function for pairs
template <typename T1, typename T2>
struct PairHash {
    std::size_t operator()(const std::pair<T1, T2>& p) const {
        // Combine the hash of the first and second elements of the pair
        return std::hash<T1>{}(p.first) ^ (std::hash<T2>{}(p.second) << 1);
    }
};

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    auto start = std::chrono::high_resolution_clock::now();

    cin >> n;
    triangles.reserve(n);
    vector<tuple<T,T,T,T>> edges;
    umap<tuple<T,T,T,T>, int, TupleHash> edge2id;
    vector<int> edge_count;
    P p_start, p_end;
    umap<pair<T,T>, vector<int>, PairHash<T,T>> point2edges;
    umap<pair<T,T>, int, PairHash<T,T>> point2id;
    vector<vector<int>> pointId2lastTriangleNeighbors;
    vector<int> pointId2lastTriangleIndex;
    pointId2lastTriangleNeighbors.reserve(3*n);
    pointId2lastTriangleIndex.reserve(3*n);

    auto get_point_id = [&](P& p) {
        auto it = point2id.find({p.x, p.y});
        if (it == point2id.end()) {
            int id = point2id.size();
            point2id[{p.x, p.y}] = id;
            return id;
        }
        return it->ss;
    };

    rep(i,0,n) {
        ll x1, y1, x2, y2, x3, y3;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        P p1(x1, y1), p2(x2, y2), p3(x3, y3);
        int p1_id = get_point_id(p1);
        int p2_id = get_point_id(p2);
        int p3_id = get_point_id(p3);
        // update neighbors
        int x = max({p1_id, p2_id, p3_id})+1;
        if (pointId2lastTriangleNeighbors.size() < x) {
            pointId2lastTriangleNeighbors.resize(x);
            pointId2lastTriangleIndex.resize(x);
        }
        pointId2lastTriangleNeighbors[p1_id].clear(); // clear previous neighbors
        pointId2lastTriangleNeighbors[p1_id].pb(p2_id);
        pointId2lastTriangleNeighbors[p1_id].pb(p3_id);
        pointId2lastTriangleNeighbors[p2_id].clear(); // clear previous neighbors
        pointId2lastTriangleNeighbors[p2_id].pb(p1_id);
        pointId2lastTriangleNeighbors[p2_id].pb(p3_id);
        pointId2lastTriangleNeighbors[p3_id].clear(); // clear previous neighbors
        pointId2lastTriangleNeighbors[p3_id].pb(p1_id);
        pointId2lastTriangleNeighbors[p3_id].pb(p2_id);
        pointId2lastTriangleIndex[p1_id] = i;
        pointId2lastTriangleIndex[p2_id] = i;
        pointId2lastTriangleIndex[p3_id] = i;
        // set start and end points
        if (i == 0) p_start = p1;
        else if (i == n-1) p_end = p3;
        // sort points counter clockwise
        if (((p2-p1)^(p3-p1)) < 0) swap(p2, p3);         
        triangles.eb(p1, p2, p3);
        // add edges
        auto edge1 = make_tuple(p1.x, p1.y, p2.x, p2.y);
        auto edge2 = make_tuple(p2.x, p2.y, p3.x, p3.y);
        auto edge3 = make_tuple(p3.x, p3.y, p1.x, p1.y);
        for (auto edge : {edge1, edge2, edge3}) {
            int edge_id;
            auto it = edge2id.find(edge);
            if (it == edge2id.end()) {
                auto reverse_edge = make_tuple(get<2>(edge), get<3>(edge), get<0>(edge), get<1>(edge));
                edge_id = edges.size();
                edge2id[edge] = edge_id;
                edge2id[reverse_edge] = edge_id;
                edges.pb(edge);
                edge_count.pb(1);
            } else {
                edge_id = it->ss;
                edge_count[edge_id]++;
            }
            point2edges[{get<0>(edge), get<1>(edge)}].pb(edge_id);
            point2edges[{get<2>(edge), get<3>(edge)}].pb(edge_id);
        }
    }

    // auto end = std::chrono::high_resolution_clock::now();

    // cout << "Elapsed time (reading input): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
    
    // // sanity check
    // for (int count : edge_count) {
    //     assert(count == 1 or count == 2); // each edge should be shared by 1 or 2 triangles
    // }

    // special case: p_start == p_end
    if (p_start == p_end) {
        cout << p_start.x << " " << p_start.y << "\n";
        return 0;
    }

    start = std::chrono::high_resolution_clock::now();

    // find border (counter clockwise)
    P current = p_start;
    int current_edge_id = -1;
    border.pb(current);
    while (true) {
        // find first border edge different from current_edge
        auto& edge_ids = point2edges[{current.x, current.y}];
        int next_edge_id = -1;
        for (int edge_id : edge_ids) {
            if (edge_id != current_edge_id and edge_count[edge_id] == 1) {
                next_edge_id = edge_id;
                break;
            }
        }
        // assert(next_edge_id != -1);
        auto next_edge = edges[next_edge_id];
        P p1(get<0>(next_edge), get<1>(next_edge));
        P p2(get<2>(next_edge), get<3>(next_edge));
        if (p1 == current) current = p2;
        else { /* assert(p2 == current); */ current = p1; }

        if (current == p_start) break; // cycle completed

        border.pb(current);
        current_edge_id = next_edge_id;
    }

    // reverse border if needed
    if (signed_area(border) < 0) reverse(border.begin(), border.end()); // counter clockwise

    // assert (border.size() == point2id.size()); // border should have the same number of points as the input

    int num_nodes = border.size();
    vector<int> pointId2borderIndex(num_nodes);
    vector<int> borderIndex2pointId(num_nodes);
    rep(i,0,num_nodes) {
        int pid = get_point_id(border[i]);
        pointId2borderIndex[pid] = i;
        borderIndex2pointId[i] = pid;
    }

    // end =  std::chrono::high_resolution_clock::now();
    // cout << "Elapsed time (building border): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    // build graph

    // start = std::chrono::high_resolution_clock::now();

    vector<vector<pair<int, double>>> g(num_nodes);
    queue<int> q;
    q.push(get_point_id(p_start));
    vector<bool> visited(num_nodes, false);
    visited[q.front()] = true;
    int end_idx = pointId2borderIndex[get_point_id(p_end)];

    // int actual_nodes = 0;
    // int total_work = 0;

    while(!q.empty()) {

        // actual_nodes++;

        int u = q.front(); q.pop();
        int u_idx = pointId2borderIndex[u];
        P pu = border[u_idx];
        vector<int>& neighbors = pointId2lastTriangleNeighbors[u];
        // assert (neighbors.size() == 2);
        int vl = neighbors[0];
        int vr = neighbors[1];
        int vl_idx = pointId2borderIndex[vl];
        int vr_idx = pointId2borderIndex[vr];
        P pl = border[vl_idx];
        P pr = border[vr_idx];

        // make sure pl is to the left of pr
        if (((pr-pu)^(pl-pu)) < 0) {
            swap(pl, pr);
            swap(vl, vr);
            swap(vl_idx, vr_idx);
        }
        
        // find farthest left and right points visible from u
        int farthest_left_idx = vl_idx;
        int farthest_right_idx = vr_idx;
        P u_to_left = pl - pu;
        P u_to_right = pr - pu;
        P next_u_to_left = u_to_left;
        P next_u_to_right = u_to_right;

        while ((u_to_right^u_to_left) >= 0) { // while there is a visibility gap
            int left_triangle_idx = pointId2lastTriangleIndex[borderIndex2pointId[vl_idx]];
            int right_triangle_idx = pointId2lastTriangleIndex[borderIndex2pointId[vr_idx]];
            // prioritize moving the pointer that is farther from the end target
            if (left_triangle_idx <= right_triangle_idx) {
                if (vl_idx != end_idx) {
                    int next_vl_idx = (vl_idx-1+num_nodes) % num_nodes;
                    next_u_to_left = border[next_vl_idx] - pu;
                    if ((next_u_to_left^u_to_left) >= 0 and
                        (next_u_to_left^u_to_right) <= 0) farthest_left_idx = next_vl_idx;
                    vl_idx = next_vl_idx;
                    // total_work++;
                }
            }
            if (right_triangle_idx <= left_triangle_idx) {
                if (vr_idx != end_idx) {
                    int next_vr_idx = (vr_idx+1) % num_nodes;
                    next_u_to_right = border[next_vr_idx] - pu;
                    if ((next_u_to_right^u_to_left) >= 0 and
                        (next_u_to_right^u_to_right) <= 0) farthest_right_idx = next_vr_idx;
                    vr_idx = next_vr_idx;
                    // total_work++;
                }
            }
            if (vl_idx == end_idx and vr_idx == end_idx) break; // no more points to check
            // update visibility range
            if ((next_u_to_left^u_to_left) > 0) u_to_left = next_u_to_left;
            if ((next_u_to_right^u_to_right) < 0) u_to_right = next_u_to_right;
        }
        // update graph
        int farthest_left_id = get_point_id(border[farthest_left_idx]);
        int farthest_right_id = get_point_id(border[farthest_right_idx]);
        g[u].pb({farthest_left_id, (border[farthest_left_idx] - pu).norm()});
        g[u].pb({farthest_right_id, (border[farthest_right_idx] - pu).norm()});
        if (!visited[farthest_left_id] and farthest_left_idx != end_idx) {
            visited[farthest_left_id] = true;
            q.push(farthest_left_id);
        }
        if (!visited[farthest_right_id] and farthest_right_idx != end_idx) {
            visited[farthest_right_id] = true;
            q.push(farthest_right_id);
        }
    }

    // end =  std::chrono::high_resolution_clock::now();
    // cout << "Elapsed time (building graph): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    // double average_work = (double)total_work / actual_nodes;
    // cout << "Average work per node: " << average_work << " (actual nodes: " << actual_nodes << ", total work: " << total_work << ")\n";

    // dijkstra

    start = std::chrono::high_resolution_clock::now();

    vector<double> distances;
    vector<int> parents;
    dijkstra(get_point_id(p_start), num_nodes, g, distances, parents);

    // end =  std::chrono::high_resolution_clock::now();
    // cout << "Elapsed time (dijkstra): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    // recover path from p_start to p_end

    // start = std::chrono::high_resolution_clock::now();

    vector<P> path;
    int current_id = get_point_id(p_end);
    while (current_id != -1) {
        path.pb(border[pointId2borderIndex[current_id]]);
        current_id = parents[current_id];
    }
    reverse(path.begin(), path.end());

    // clean path by removing intermediate points that are collinear
    vector<P> clean_path;
    clean_path.pb(path[0]);
    rep(i,1,path.size()-1) {
        if (((path[i-1]-path[i])^(path[i+1]-path[i])) != 0) clean_path.pb(path[i]);
    }
    clean_path.pb(path.back());

    // end =  std::chrono::high_resolution_clock::now();
    // cout << "Elapsed time (recovering path): " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";

    // print path
    for (P& p : clean_path) cout << p.x << " " << p.y << "\n";

    // // save graph to txt (for debugging)
    // save_graph_to_txt(g, pointId2borderIndex, border, p_start, p_end);

    return 0;
}