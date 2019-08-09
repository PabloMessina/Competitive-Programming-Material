// tags: greedy, std::priority_queue, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
const int MAXN = 500000;
int N,M;
int X[MAXN], L[MAXN];
struct Interval {
    int i, j, len;
    Interval(int i, int j) : i(i), j(j) {
        len = X[j] - X[i];
    }
    bool operator<(const Interval& rhs) const {
        return len > rhs.len;
    }
};
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    rep(i,0,N-1) cin >> X[i];
    rep(i,0,M-1) cin >> L[i];
    sort(L, L+M);
    priority_queue<Interval> q;
    int i = 0;
    rep(j,0,N-2) q.emplace(j,j+1);
    while (!q.empty() and i < M) {
        auto& x = q.top();
        if (x.len > L[i]) break;
        if (x.j + 1 < N) q.emplace(x.i, x.j+1);
        q.pop();
        ++i;
    }
    if (i == M) cout << "yes\n";
    else cout << "no\n";
    return 0;
}