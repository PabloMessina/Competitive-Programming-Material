#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
typedef vector<int> vi;
typedef pair<int,int> ii;
// -------------------------------
int N, M, P;
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> N >> M >> P and N) {
        vector<pair<int,int>> plants;
        rep(i,0,P) {
            int r,c; cin >> r >> c; --r, --c;
            plants.emplace_back(r,c);
        }
        vector<tuple<int,int,int>> ranking;
        rep(r,0,N) rep(c,0,M) {
            int mindist = INT_MAX;
            rep(i,0,P) {
                auto& p = plants[i];
                int dist = max(abs(p.first - r), abs(p.second - c));
                mindist = min(mindist, dist);                
            }
            if (mindist == 0) continue;
            ranking.emplace_back(mindist, r, c);
        }
        sort(ranking.begin(), ranking.end());
        int Q; cin >> Q;
        while (Q--) {
            int p; cin >> p; --p;
            int _, r, c; tie(_,r,c) = ranking[p];
            cout << r+1 << ' ' << c+1 << '\n';
        }
        cout << "-\n";
    }
    return 0;
}