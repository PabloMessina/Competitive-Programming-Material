// tags: implementation
#include <bits/stdc++.h> // import everything in one shot
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i <= b; ++i)
// -------------------------------

int row[26], col[26];
int dist(string& x, string& y) { // compute distance between strings x and y
    int n = x.size();
    int ans = 0;
    rep(i,0,n-1) {
        int jx = x[i] - 'a';
        int jy = y[i] - 'a';
        int rx = row[jx], cx = col[jx];
        int ry = row[jy], cy = col[jy];
        ans += abs(rx - ry) + abs(cx - cy);
    }
    return ans;
}

int main() {
    // 1) map each char to its row and column
    int i = 0;
    for (char c : string("qwertyuiop")) {
        int j = c - 'a';
        row[j] = 0;
        col[j] = i++;
    }
    i = 0;
    for (char c : string("asdfghjkl")) {
        int j = c - 'a';
        row[j] = 1;
        col[j] = i++;
    }
    i = 0;
    for (char c : string("zxcvbnm")) {
        int j = c - 'a';
        row[j] = 2;
        col[j] = i++;
    }
    // 2) read input and solve problem
    int T; cin >> T;
    while (T--) {
        string word; int l;
        cin >> word >> l;
        // collect (distance, string) pairs
        vector<pair<int,string>> pairs;
        while (l--) {
            string s; cin >> s;
            pairs.emplace_back(dist(word, s), s);
        }
        // sort the pairs
        sort(pairs.begin(), pairs.end());
        // print the pairs
        for (auto& p : pairs) {
            cout << p.second << " " << p.first << endl;
        }
    }
    return 0;
}