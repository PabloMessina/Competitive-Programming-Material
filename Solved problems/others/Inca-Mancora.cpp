#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int N, M, Q;
int table[10000][10000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M >> Q;
    while (M--) {
        int k, a, b;
        cin >> k >> a >> b;
        assert (a < b);
        --a, -- b;
        table[a][b]++;
        if (b + k < N) {
            table[a+k][b+k]--;
        }
    }
    rep(r,0,N) {
        int i = r;
        int j = 0;
        int sum = 0;
        while (i < N and j < N) {
            sum += table[i][j];
            table[i][j] = sum;
            ++i, ++j;
        }
    }
    rep(c,1,N) {
        int i = 0;
        int j = c;
        int sum = 0;
        while (i < N and j < N) {
            sum += table[i][j];
            table[i][j] = sum;
            ++i, ++j;
        }
    }
    while (Q--) {
        int x, y; cin >> x >> y;
        --x, --y;
        if ((table[x][y] & 1) or (table[y][x] & 1)) {
            cout << "SI\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}