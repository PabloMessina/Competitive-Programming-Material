// tags: math, linear equation system, gaussian elimination, matrix
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
// source: https://cp-algorithms.com/linear_algebra/linear-system-gauss.html
const double EPS = 1e-9;
const int INF = 2;
int gauss (vector<vector<double>>& a, vector<double>& ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;
    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        rep(i,row,n) if (abs(a[i][col]) > abs(a[sel][col])) sel = i;
        if (abs(a[sel][col]) < EPS) continue;
        rep(i,col,m+1) swap(a[sel][i], a[row][i]);
        where[col] = row;
        rep(i,0,n) if (i != row) {
            double c = a[i][col] / a[row][col];
            rep(j,col,m+1) a[i][j] -= a[row][j] * c;
        }
        ++row;
    }
    ans.assign (m, 0);
    rep(i,0,m) if (where[i] != -1) {
        ans[i] = a[where[i]][m] / a[where[i]][i];
    }
    rep(i,0,n) {
        double sum = 0;
        rep(j,0,m) sum += ans[j] * a[i][j];
        if (abs(sum - a[i][m]) > EPS) return 0;
    }
    rep(i,0,m) if (where[i] == -1) return INF;
    return 1;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, s, e; cin >> n >> s >> e; --s, --e;
        vector<vector<double>> A(n, vector<double>(n + 1, 0.));
        rep(_,1,n) {
            int u, v; double c;
            cin >> u >> v >> c; --u, -- v;
            A[u][v] = c;
            A[v][u] = c;
        }
        rep(i,0,n) {
            if (i == e) continue;      
            double sum = 0.;
            for (double& x : A[i]) sum += x;
            rep(j,0,n) {
                if (A[i][j] > EPS) {
                    A[i][j] = - A[i][j] / sum;
                }
            }
            A[i][i] = 1.0;
        }
        rep(i,0,n) {
            A[e][i] = A[i][e] = 0.;
            A[i][n] = 1.;
        }
        A[e][e] = 1.;
        A[e][n] = 0.;
        vector<double> ans;
        assert (gauss(A, ans) == 1); // TODO: proof
        cout << setprecision(5) << fixed << ans[s] << '\n';
    }
    return 0;
}