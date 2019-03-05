// tags: backtracking, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int N;
int vals[5];

int solve(int depth) {
    int count = 0;
    rep(i, 0, N-2) {
        if (vals[i] > vals[i+1]) {
            swap(vals[i], vals[i+1]);
            count += solve(depth+1);
            swap(vals[i], vals[i+1]);
        }
    }
    if (depth == 0) return count;
    else return max(count, 1);
}

int main() {
    int _case = 1;
    while (cin >> N and N) {
        rep(i,0,N-1) cin >> vals[i];
        cout << "There are " << solve(0) <<
                " swap maps for input data set " << _case << ".\n";
        _case++;
    }
    return 0;
}