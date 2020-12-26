// tags: DP, implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define uset unordered_set
// -------------------------------
vector<int> nums;
vector<char> ops;
uset<int> sums;
int n, true_ = 1;

int memo[30][6001][30];
void search(int i, int s, int p) {
    if (i == n) {
        sums.insert(s);
        return;
    }
    int& solved = memo[i][s+3000][p];
    if (solved == true_) return;
    solved = true_;
    s += p % 2 ? -nums[i] : nums[i];
    search(i+1, s, p);
    if (p > 0) search(i+1, s, p-1);
    if (ops[i] == '-') search(i+1, s, p+1);
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        nums.clear();
        ops.clear();
        int x; char op;
        ss >> x;
        nums.push_back(x);
        ops.push_back('+');
        while (ss >> op >> x) {
            if (op == '-') x = -x;
            nums.push_back(x);
            ops.push_back(op);
        }
        n = nums.size();
        sums.clear();
        search(0, 0, 0);
        cout << sums.size() << '\n';
        true_++;
    }
    return 0;
}