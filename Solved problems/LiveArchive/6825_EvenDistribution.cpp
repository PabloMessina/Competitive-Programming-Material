// tags: BFS, GCD
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
const int MAXI = 10000;
const int MAXC = 100000;
int I,S;
int candies[MAXI];
vector<vector<int>> g;
uset<int> found_nums;
set<ii> states;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    while (cin >> I >> S) {
        g.assign(I, vector<int>());
        rep(i,0,I) cin >> candies[i];
        rep(i,1,S+1) {
            int a, b; cin >> a >> b; --a, --b;
            g[a].push_back(b);
            g[b].push_back(a);
        }
        queue<ii> q;        
        found_nums.clear();
        states.clear();
        rep(i,0,I) {
            ii state(i, candies[i]);
            q.push(state);
            states.insert(state);
            found_nums.insert(candies[i]);
        }
        while (!q.empty()) {
            ii front = q.front(); q.pop();
            int u = front.first, c = front.second;
            for (int v : g[u]) {
                int cc = __gcd(candies[v], c);
                ii state(v, cc);
                if (!states.count(state)) {
                    states.insert(state);
                    found_nums.insert(cc);
                    q.push(state);
                }
            }
        }
        cout << found_nums.size() << '\n';
    }
    return 0;
}