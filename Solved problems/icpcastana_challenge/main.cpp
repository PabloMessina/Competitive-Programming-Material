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

// input variables
int npu, tor, spine;
vector<int> s;
int n1, t1, n2, t2;
vector<int> a1, a2;
vector<int> ks1, ks2;
vector<int> latencies1, latencies2;
vector<vector<ii>> edges1, edges2;

// output variables
vector<int> rank1, rank2;
int m1, m2;
vector<tuple<int,int,int>> rules1, rules2;

void read_task(int& n, int& t, vector<int>& a, vector<int>& ks, vector<int>& latencies, vector<vector<ii>>& edges) {
    std::cin >> n >> t;
    rep(i,0,n) {
        int x;
        std::cin >> x;
        a.pb(x);
    }
    rep(i,0,t) {
        int k, latency;
        std::cin >> k >> latency;
        ks.pb(k);
        latencies.pb(latency);
        vector<ii> e;
        rep(j,0,k) {
            int u, v;
            std::cin >> u >> v;
            e.eb(u, v);
        }
        edges.pb(e);
    }
}

void print_task(int n, int m, const vector<int>& rank, const vector<tuple<int,int,int>>& rules) {
    // print rank
    rep(i,0,n) {
        if (i) std::cout << " ";
        std::cout << rank[i];
    }
    std::cout << '\n';
    // print m
    std::cout << m << '\n';
    // print rules
    rep(i,0,m) {
        int u, v, sp;
        std::tie(u, v, sp) = rules[i];
        std::cout << u << " " << v << " " << sp << '\n';
    }
}

void solve_task_random(int n, int t, const vector<int>& a, const vector<int>& ks,
                    const vector<int>& latencies, const vector<vector<ii>>& edges,
                    vector<int>& rank, int& m, vector<tuple<int,int,int>>& rules) {
    // random rank
    rank.resize(n);
    iota(rank.begin(), rank.end(), 0);
    random_shuffle(rank.begin(), rank.end());
    // random m and rules
    map<ii, int> edge2spine;
    rep(i,0,t) {
        rep(j,0,ks[i]) {
            edge2spine[edges[i][j]] = rand() % spine;
        }
    }
    m = edge2spine.size();
    for (auto& p : edge2spine) {
        int u, v;
        tie(u, v) = p.first;
        rules.eb(u, v, p.second);
    }
}

int main() {
    ios::sync_with_stdio(false); std::cin.tie(0);
    std::cin >> npu >> tor >> spine;

    // read all ints from the next line into s
    string line;
    getline(std::cin, line);
    getline(std::cin, line);
    istringstream iss(line);
    int x;
    while (iss >> x) s.pb(x);

    // read task 1
    read_task(n1, t1, a1, ks1, latencies1, edges1);
    // read task 2
    read_task(n2, t2, a2, ks2, latencies2, edges2);

    // solve tasks
    solve_task_random(n1, t1, a1, ks1, latencies1, edges1, rank1, m1, rules1);
    solve_task_random(n2, t2, a2, ks2, latencies2, edges2, rank2, m2, rules2);

    // print output
    print_task(n1, m1, rank1, rules1);
    print_task(n2, m2, rank2, rules2);

    return 0;
}