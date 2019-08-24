// tags: fenwick tree 2D
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
struct BIT2D {
    vector<int> bit;
    int R, C;
    BIT2D(int _R, int _C) : R(_R), C(_C) {
        bit.assign((R+1)*(C+1), 0);
    }
    void add(int r, int c, int value) {
        for (int i = r; i <= R; i += (i&-i))
            for (int j = c; j <= C; j += (j&-j))
                bit[i * C + j] += value;
    }
    int sum(int r, int c) {
        int res = 0;
        for (int i = r; i; i -= (i&-i))
            for (int j = c; j; j -= (j&-j))
                res += bit[i * C + j];
        return res;
    }
    int sum(int r1, int c1, int r2, int c2) {
        return sum(r2, c2) - sum(r1-1, c2) - sum(r2, c1-1) + sum(r1-1, c1-1);
    }
    int get(int r, int c) {
        return sum(r, c, r, c);
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--) {
        int N; cin >> N;
        BIT2D bit(N,N);
        string op;
        while (1) {
            cin >> op;
            if (op == "END") break;
            if (op == "SET") {
                int x, y, v; cin >> x >> y >> v;
                bit.add(x+1, y+1, -bit.get(x+1, y+1) + v);
            } else {
                int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
                cout << bit.sum(x1+1, y1+1, x2+1, y2+1) << '\n';
            }
        }
        cout << '\n';
    }
    return 0;
}