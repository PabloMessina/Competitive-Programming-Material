// tags: implementation, bitwise
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i=a; i<=b; ++i)
typedef pair<int,int> ii;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    string line; getline(cin,line);
    vector<ii> brackets;
    stack<int> indexes;
    int i = 0;
    for (char c : line) {
        if (c == '(') indexes.push(i);
        else if (c == ')') {
            brackets.emplace_back(indexes.top(), i);
            indexes.pop();
        }
        i++;
    }
    int n = line.size();
    bool skip[n];
    char buf[n + 1];
    set<string> expressions;
    int mask = 1 << brackets.size();
    while (--mask) {
        memset(skip, 0, sizeof skip);
        int j = 0;
        for (auto& p : brackets) {
            if ((mask >> j) & 1) {
                skip[p.first] = true;
                skip[p.second] = true;
            }
            j++;
        }
        j = 0;
        int m = 0;
        for (char c : line) {
            if (!skip[j]) buf[m++] = c;
            j++;
        }
        buf[m] = '\0';
        expressions.insert(string(buf));
    }
    for (const string& s : expressions) cout << s << '\n';
    return 0;
}