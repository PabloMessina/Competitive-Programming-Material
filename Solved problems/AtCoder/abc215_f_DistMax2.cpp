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
const int MAXN = 2e5+5;
int N;
int X[MAXN], Y[MAXN], x2i[MAXN], y2i[MAXN];
int xmin, xmax, ymin, ymax;

int clip(int x, int a, int b) {
    return max(a, min(b, x));
}

int query(int x1, int y1, int x2, int y2, vector<vector<int>>& grid) {
    x1 = clip(x1, xmin, xmax);
    x2 = clip(x2, xmin, xmax);
    y1 = clip(y1, ymin, ymax);
    y2 = clip(y2, ymin, ymax);
    if (x1 > x2 || y1 > y2) return 0;
    x1 = x2i[x1];
    x2 = x2i[x2];
    y1 = y2i[y1];
    y2 = y2i[y2];
    int ans = grid[x2][y2];
    if (x1 > 0) ans -= grid[x1-1][y2];
    if (y1 > 0) ans -= grid[x2][y1-1];
    if (x1 > 0 && y1 > 0) ans += grid[x1-1][y1-1];
    return ans;
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    // read input
    cin >> N;
    set<int> uniqueX, uniqueY;
    rep(i,0,N) {
        cin >> X[i] >> Y[i];
        uniqueX.insert(X[i]);
        uniqueY.insert(Y[i]);
    }
    // compress coordinates
    int i = 0;
    for (int x : uniqueX) x2i[x] = i++;
    i = 0;
    for (int y : uniqueY) y2i[y] = i++;
    // build grid and count points
    vector<vector<int>> grid(uniqueX.size(), vector<int>(uniqueY.size(), 0));
    rep(i,0,N) grid[x2i[X[i]]][y2i[Y[i]]]++;
    // build prefix sums
    rep(i,0,uniqueX.size()) rep(j,0,uniqueY.size()) {
        if (i > 0) grid[i][j] += grid[i-1][j];
        if (j > 0) grid[i][j] += grid[i][j-1];
        if (i > 0 && j > 0) grid[i][j] -= grid[i-1][j-1];
    }
    // find max distance with binary search
    xmin = *uniqueX.begin();
    xmax = *uniqueX.rbegin();
    ymin = *uniqueY.begin();
    ymax = *uniqueY.rbegin();
    int l = 0, r = 1e9 + 5;
    while (l < r) {
        int m = (l+r) >> 1;
        bool possible = false;
        rep(i,0,N) {
            // check if there is a point outside a square of side 2*(m-1) centered at (X[i], Y[i])
            int x1 = X[i] - m + 1, y1 = Y[i] - m + 1;
            int x2 = X[i] + m - 1, y2 = Y[i] + m - 1;
            if (query(x1, y1, x2, y2, grid) < N) { // there is a point outside the square
                possible = true;
                break;
            }
        }
        if (possible) {
            r = m;
        } else {
            l = m+1;
        }
    }
    cout << l-1 << '\n';
    return 0;
}