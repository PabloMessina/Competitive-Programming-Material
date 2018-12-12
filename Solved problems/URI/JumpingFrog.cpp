// tags: modular arithmetics, gcd, math, DP, memoization
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

string input;
int N;
int memo[100000];
int valid(int g) {
    int& ans = memo[g];
    if (ans != -1) return ans;
    int k = N / g;
    rep(i,0,g-1) {
        bool works = true;
        rep(x,1,k) {
            if (input[(i + x * g) % N] != 'R') {
                works = false; break;
            }
        }
        if (works) return ans = 1;
    }
    return ans = 0;
}

int main() {
    cin >> input;
    N = input.size();
    memset(memo, -1, sizeof(int) * N);
    int count = 0;    
    rep(k,1,N-1) {
        int g = __gcd(k,N);
        if (valid(g)) count++;
    }
    cout << count << '\n';
    return 0;
}