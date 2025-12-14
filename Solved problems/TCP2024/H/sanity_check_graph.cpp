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

void dijkstra(int s, int N, vector<vector<pair<int, double>>>& g, vector<double>& D, vector<int>& P) {
    P.assign(N, -1);
    D.assign(N, DBL_MAX);
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

int main() {
    ios::sync_with_stdio(false); cin.tie(0);

    ll root_x, root_y;
    cin >> root_x >> root_y;

    ll target_x, target_y;
    cin >> target_x >> target_y;

    vector<vector<pair<int, double>>> g;
    map<pair<ll, ll>, int> point2id;

    ll x1, y1, x2, y2;
    while (cin >> x1 >> y1 >> x2 >> y2) {
        if (point2id.find({x1, y1}) == point2id.end()) {
            int id = point2id.size();
            point2id[{x1, y1}] = id;
            g.pb({});
        }
        if (point2id.find({x2, y2}) == point2id.end()) {
            int id = point2id.size();
            point2id[{x2, y2}] = id;
            g.pb({});
        }
        int id1 = point2id[{x1, y1}];
        int id2 = point2id[{x2, y2}];
        g[id1].pb({id2, sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))});
        g[id2].pb({id1, sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2))});
    }

    vector<int> P;
    vector<double> D;
    int root_id = point2id[{root_x, root_y}];
    int target_id = point2id[{target_x, target_y}];
    dijkstra(root_id, point2id.size(), g, D, P);

    cout << "point2id.size(): " << point2id.size() << "\n";
    cout << "root_id: " << root_id << "\n";    
    cout << "D[root_id]: " << D[root_id] << "\n";
    cout << "target_id: " << target_id << "\n";
    cout << "D[target_id]: " << D[target_id] << "\n";

    return 0;
}