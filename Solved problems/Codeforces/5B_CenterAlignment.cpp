// tags: implementation
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    ios::sync_with_stdio(false); cin.tie(0); // c++ magic, optimización de input
    vector<string> lines;
    string line;
    int maxlen = 0; // 32 bits
    while (getline(cin, line)) {
        lines.push_back(line); // en python: lines.append(line)
        if (maxlen < line.size()) 
            maxlen = line.size();
        // maxlen = max(maxlen, line.size());
    }
    rep(i,0,maxlen+2) cout << '*';
    cout << '\n';
    bool left = true;
    for (string& line : lines) { // C++11
        int space = maxlen - line.size();
        int lpad, rpad;
        if (space % 2 == 0) {
            lpad = rpad = space / 2;
        } else if (left) {
            lpad = space / 2;
            rpad = space - lpad;
            left = false;
        } else {
            rpad = space / 2;
            lpad = space - rpad;
            left = true;
        }
        cout << '*';
        rep(i,0,lpad) cout << ' ';
        cout << line;
        rep(i,0,rpad) cout << ' ';
        cout << "*\n";
    }
    rep(i,0,maxlen+2) cout << '*';
    cout << '\n';
    return 0;
}