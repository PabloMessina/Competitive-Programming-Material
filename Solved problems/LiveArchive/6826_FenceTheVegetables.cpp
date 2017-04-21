#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; i++)
#define invrep(i,a,b) for(int i=a; i>=b; i--)
typedef pair<int,int> ii;

int V;
vector<ii> pts;
vector<ii> margin_pts;
map<int, ii> x2minmaxy;

int dirs[4][2] = {
    {-1, -1},
    {1, -1},
    {-1, 1},
    {1, 1}
};

int main() {
    scanf("%d", &V);
    rep(i,1,V) {
        int x, y; scanf("%d%d",&x, &y);
        pts.emplace_back(x, y);
    }

    for (auto &p : pts) {
        int x = p.first, y = p.second;
        rep(i,0,3) {
            int xx = x + dirs[i][0];
            int yy = y + dirs[i][1];
            auto it = x2minmaxy.find(xx);
            if (it == x2minmaxy.end()) {
                x2minmaxy[xx] = ii(yy, yy);
            } else {
                it.second->first = min(yy, it.second->first);
                it.second->second = max(yy, it.second->second);
            }
        }
    }

    int n = (int) x2minmaxy.size();
    int acc_max_y[n];
    for (auto& it = x2minmaxy.rbegin(), it != x2minmaxy.rend(), ++it) {
    }

    for (auto &it : x2minmaxy) {
        int x = it.first;
        int min_y = it.second->first;
        int max_y = it.second->second;

        if (margin_pts.size() == 0) {
            margin_pts.emplace_back(x, max_y);
        } else {
            ii& prev_p = margin_pts.back();
            
        }
    }

  return 0;
}