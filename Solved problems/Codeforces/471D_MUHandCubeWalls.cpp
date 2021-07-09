// tags: strings, kmp
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
#define ff first
#define ss second
#define pb push_back
#define eb emplace_back
// typedefs
typedef vector<int> vi;
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
void init_lps(vector<int>& pattern, int lps[]) {
    int n = pattern.size();
    lps[0] = 0;
    rep(j, 1, n) {
        int i = lps[j-1];
        while (pattern[i] != pattern[j] and i > 0) i = lps[i-1];
        lps[j] = pattern[i] == pattern[j] ? i+1 : 0;
    }
}
int count_matches(vector<int>& pattern, vector<int>& target) {
    int n = pattern.size(), m = target.size();
    int lps[n];
    init_lps(pattern, lps);
    int matches = 0;
    int i = 0;
    rep(j, 0, m) {
        while (pattern[i] != target[j] and i > 0) i = lps[i-1];
        if (pattern[i] == target[j]) {
            if (++i == n) {
                i = lps[n-1];
                matches++;
            }
        }
    }
    return matches;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int n, w; cin >> n >> w;
    if (w > n) { cout << "0\n"; return 0; }
    if (w == 1) { cout << n << '\n'; return 0; }
    vector<int> s(n), p(w);
    for (int& x : s) cin >> x;
    for (int& x : p) cin >> x;
    rep(i, 0, n-1) s[i] -= s[i+1];
    rep(i, 0, w-1) p[i] -= p[i+1];
    s.resize(n-1);
    p.resize(w-1);
    cout << count_matches(p, s) << '\n';
    return 0;
}