// tags: strings, KMP
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
// -------------------------------
void init_lps(string& pattern, int lps[]) {
    int n = pattern.size(); lps[0] = 0;
    rep(j,1,n) {
        int i = lps[j-1];
        while (pattern[i] != pattern[j] and i > 0) i = lps[i-1];
        lps[j] = pattern[i] == pattern[j] ? i+1 : 0;
    }
}
int find(string& pattern, string& target) {
    int n = pattern.size(), m = target.size();
    int lps[n];
    init_lps(pattern, lps);
    int i = 0;
    rep(j,0,m) {
        while (pattern[i] != target[j] and i > 0) i = lps[i-1];
        if (pattern[i] == target[j]) if (++i == n) return (n - (j - n + 1)) % n;
    }
    return -1;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n; cin >> n; string a, b;
    a.reserve(2*n); cin >> a >> b; a += a;
    cout << find(b, a) << '\n';
    return 0;
}