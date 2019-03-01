// tags: backtracking, pruning, implementation, bitwise operations
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int N;
int price[1000];
int masks[1000];
int mincost = INT_MAX;
const int DONE = 7;

int string2mask(string& s) {
    int mask = 0;
    for (char c : s) mask |= 1 << (c - 'A');
    return mask;
}

void _search(int i, int mask, int cost) {
    if (mask == DONE) {
        mincost = min(mincost, cost);
        return;
    }
    if (i == N) return;
    if (cost > mincost) return;
    if ((mask | masks[i]) > mask) {
        _search(i+1, mask | masks[i], cost + price[i]);
    }
    _search(i+1, mask, cost);
}

int main() {
    cin >> N;
    string tmp;
    rep(i,0,N-1) {
        cin >> price[i] >> tmp;
        masks[i] = string2mask(tmp);
    }
    _search(0,0,0);
    cout << (mincost == INT_MAX ? -1 : mincost) << '\n';
    return 0;
}