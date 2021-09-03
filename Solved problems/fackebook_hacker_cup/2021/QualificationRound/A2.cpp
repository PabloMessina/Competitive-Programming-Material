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
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int T; cin >> T;
    rep(t,1,T+1) {
        string s; int K; cin >> s >> K;
        vector<vi> g(26, vi());
        while (K--) {
            char a, b; cin >> a >> b;
            g[a - 'A'].push_back(b - 'A');            
        }
        vector<vi> D(26, vi(26, -1));
        rep(i,0,26) {
            queue<int> q; q.push(i);
            D[i][i] = 0;
            while (q.size()) {
                int u = q.front(); q.pop();
                for (int v : g[u]) {
                    if (D[i][v] == -1) {
                        D[i][v] = D[i][u] + 1;
                        q.push(v);
                    }
                }
            }
        }
        int ans = INT_MAX;
        rep(i,0,26) {
            bool valid = true;
            int sum = 0;
            for (char c : s) {
                int j = c - 'A';
                if (D[j][i] == -1) { valid = false; break; }
                sum += D[j][i];
            }
            if (valid) ans = min(ans, sum);
        }
        if (ans == INT_MAX) ans = -1;
        cout << "Case #" << t << ": " << ans << '\n';
    }
    return 0;
}