// tags: backtracking, pruning, implementation, bitwise operations
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------
int N; // number of juices
int price[1000]; // juices' prices
int masks[1000]; // juices' bitmasks
int mincost = INT_MAX; // best solution overall
const int DONE = 7; // 7 = 111 (3 vitamins)
// convert string 's' to bitmask
// bit 1 = whether A is present
// bit 2 = whether B is present
// bit 3 = whether C is present
// exampleS: "ABC" = 111, "AC" = 101, "AB" = 011
int string2mask(string& s) {
    int mask = 0;
    for (char c : s) mask |= 1 << (c - 'A');
    return mask;
}
// i = index of juice we are currently considering (0 <= i <= N-1)
// mask = an int whose bits indicate the vitamins we already have
// cost = the total price we already have to pay
void solve(int i, int mask, int cost) {
    if (mask == DONE) { // mask = 7 = 111 (base 2) = we have the 3 vitamins
        mincost = min(mincost, cost); // update best solution
        return; // we are done
    }
    if (i == N) return; // out of range -> we are done
    if (cost > mincost) return; // partial solution is worse than best solution -> stop exploring
    // ----------------
    // here we have 2 options:
    // OPTION 1: buy i-th juice
    if ((mask | masks[i]) > mask) { // buy i-th juice only if it will provide new vitamins
        solve(i+1, mask | masks[i], cost + price[i]);
    }
    // OPTION 2: don't buy i-th juice
    solve(i+1, mask, cost);
}
int main() {
    cin >> N; // number of juices
    string tmp;
    rep(i,0,N-1) {
        cin >> price[i] >> tmp; // read price and string
        masks[i] = string2mask(tmp); // convert string to bitmask        
    }
    // search for the minimum cost solution with backtracking
    solve(0,0,0);
    // print answer
    cout << (mincost == INT_MAX ? -1 : mincost) << '\n';
    return 0;
}