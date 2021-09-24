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
        int n, m, a, b; cin >> n >> m >> a >> b;
        cout << "Case #" << t << ": ";        
        if ((n == 1 or m == 1 and a != b) or (n + m - 1 > min(a, b))) {
            cout << "Impossible\n";
            continue;
        }
        vector<vector<int>> mat(n, vector<int>(m, 0));
        mat[0][0] = a - (n-1) - (m-1);
        rep(i,1,n) mat[i][0] = 1;
        rep(i,1,m) mat[n-1][i] = 1;
        if (n > 1 and m > 1) {
            mat[0][m-1] = b - (n-1) - (m-1);
            rep(i,1,n) mat[i][m-1] = 1;
        }
        cout << "Possible\n";
        rep(i,0,n) {
            rep(j,0,m) {
                int x = mat[i][j]; if (x == 0) x = 1000;
                if (j) cout << ' ';
                cout << x;
            }
            cout << '\n';
        }
    }
    return 0;
}