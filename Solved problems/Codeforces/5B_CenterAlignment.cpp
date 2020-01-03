// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    vector<string> lines;
    string line;
    int maxlen = 0;
    while (getline(cin, line)) {
        lines.push_back(line);
        if (maxlen < line.size()) maxlen = line.size();
    }
    rep(i,0,maxlen+2) cout << '*';
    cout << '\n';
    bool left = true;
    for (string& line : lines) {
        int s = maxlen - line.size();
        int s1, s2;
        if (s % 2 == 0) {
            s1 = s2 = s/2;
        } else {
            if (left) {
                s1 = s/2;
                s2 = s - s1;
                left = false;
            } else {
                s2 = s/2;
                s1 = s - s2;
                left = true;
            }
        }
        cout << '*';
        rep(i,0,s1) cout << ' ';
        cout << line;
        rep(i,0,s2) cout << ' ';
        cout << "*\n";
    }
    rep(i,0,maxlen+2) cout << '*';
    cout << '\n';
    return 0;
}