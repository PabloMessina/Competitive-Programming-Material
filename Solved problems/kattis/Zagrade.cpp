// tags: implementation, bitmask, bitwise
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string line; cin >> line;
    stack<int> s;
    vector<pair<int,int>> brackets;
    rep(i, 0, line.size()) {
        if (line[i] == '(') s.push(i);
        else if (line[i] == ')') {
            brackets.emplace_back(s.top(), i); // C++11
            s.pop();            
        }
    }
    int n = brackets.size();
    vector<bool> skip;
    set<string> expressions;
    rep(mask, 1, 1 << n) {
        skip.assign(line.size(), false);
        int j = 0;        
        for (auto& b : brackets) {
            if (mask & (1 << j)) {
                skip[b.first] = true;
                skip[b.second] = true;
            }
            ++j;
        }
        string exp = "";
        rep(i, 0, line.size()) {
            if (skip[i]) continue;
            exp += line[i];
        }
        expressions.insert(exp);
    }
    for (auto& exp : expressions) cout << exp << '\n';
    return 0;
}