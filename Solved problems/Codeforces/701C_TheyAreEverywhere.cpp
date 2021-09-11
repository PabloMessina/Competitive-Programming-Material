// tags: implementation, two pointers
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
int acc[52][100000];
int char2int(char c) {
    if ('a' <= c and c <= 'z') return c - 'a';
    return 26 + (c - 'A');
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n;
    string line; cin >> line;
    rep(i,0,n) {
        if (i > 0) rep(j,0,52) acc[j][i] = acc[j][i-1];
        int p = char2int(line[i]);
        acc[p][i]++;
    }
    vector<int> pok;
    rep(i,0,52) {
        if (acc[i][n-1] > 0)
            pok.push_back(i);
    }
    int ans = n;
    int j = 0;
    rep(i,0,n) {
        while (j < i) j++;
        while (j < n) {
            bool done = true;
            for (int p : pok) {
                int f  = acc[p][j] - (i-1 >= 0 ? acc[p][i-1] : 0);
                if (f == 0) {
                    done = false;
                    break;
                }
            }
            if (done) {
                ans = min(ans, j - i + 1);
                break;
            }
            ++j;
        }
    }
    cout << ans << '\n';
    return 0;
}