// tags: implicit graph, BFS, math, modular arithmetics
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
// -------------------------------
pair<int,int> prev_[500][5001];
int num[500][5001];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int d, s; cin >> d >> s;
    rep(i,0,d) rep(j,0,s+1) num[i][j] = -1;
    int ur, us;
    queue<pair<int,int>> q;
    rep(k, 1, 10) {
        ur = k % d;
        us = k;
        if (ur == 0 and us == s) {
            cout << k << '\n';
            return 0;
        }
        q.emplace(ur, us);
        num[ur][us] = k;
        prev_[ur][us] = {ur, us};
    }
    while (!q.empty()) {
        tie(ur, us) = q.front(); q.pop();
        rep(k,0,10) {
            int vr = (ur * 10 + k) % d;
            int vs = us + k;
            if (vr == 0 and vs == s) {
                vector<int> ans;
                ans.push_back(k);
                int pr = ur, ps = us;
                while (1) {
                    ans.push_back(num[pr][ps]);
                    auto tmp = prev_[pr][ps];
                    if (pr == tmp.first and ps == tmp.second) break;
                    tie(pr, ps) = tmp;
                }
                reverse(ans.begin(), ans.end());
                for (int x : ans) cout << x;
                cout << '\n';
                return 0;
            }
            if (vs <= s and num[vr][vs] == -1)  {
                num[vr][vs] = k;
                prev_[vr][vs] = {ur, us};
                q.emplace(vr, vs);
            }
        }
    }
    cout << "-1\n";
    return 0;
}