// tags: backtracking, pruning, greedy
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
#define uset unordered_set
// -------------------------------

stack<int> stacks[50];
uset<int> squares;
int N;
int xmax;

void search(int i, int x) {
    bool worked = false;
    rep(j,0,i-1) {
        stack<int>& s = stacks[j];
        if (squares.count(s.top() + x)) {
            worked = true;
            s.push(x);
            xmax = max(xmax, x);
            search(i, x+1);
            s.pop();
        }
    }
    if (i < N and !worked) {
        stack<int>& s = stacks[i];
        s.push(x);
        xmax = max(xmax, x);
        search(i+1, x+1);
        s.pop();
    }
}

int main() {
    for (int x=1; x < INT_MAX/x; ++x)
        squares.insert(x*x);
    int T; cin >> T;
    while (T--) {
        cin >> N;
        xmax = 0;
        search(0,1);
        cout << xmax << '\n';
    }
    return 0;
}