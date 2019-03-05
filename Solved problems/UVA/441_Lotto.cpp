// tags: backtracking, implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int k;
int vals[13];
vector<int> s;

void print_stack() {
    cout << s[0];
    rep(i,1,s.size()-1) cout << " " << s[i];
    cout << '\n';
}

void solve(int i) {
    int n = s.size(); // number of values currently in stack
    int p = 6 - n; // number of pending values to complete a stack of 6 values
    int c = k - i; // number of candidate values from index i to the right
    if (p == 0) { // no pending values, stack is complete, we are done
        print_stack();
        return;
    }
    // stack not complete yet, we still need to add 'p' more values
    assert(p > 0);
    assert(c >= p);
    // option 1: add i-th value to stack
    s.push_back(vals[i]);
    solve(i+1);
    s.pop_back();
    // option 2: do not add i-th value to stack (only if possible)
    if (c > p) solve(i+1);
}

int main() {
    int _count = 0;
    while (true) {
        cin >> k;
        if (k == 0) break; // no more test cases
        rep(i,0,k-1) cin >> vals[i];
        if (_count++) cout << '\n';
        solve(0);
    }
    return 0;
}