// tags: implementation
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
// typedefs
typedef pair<int,int> ii;
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
string s;
int n;
int freq[26][131072];
int get_freq(int i, int j, char c) {
    return freq[c-'a'][j] - (i > 0 ? freq[c-'a'][i-1] : 0);
}
int mincost(int l, int r, char c) {
    int len = r - l;
    if (len == 1) return s[l] != c;
    int hlen = len / 2;
    int cost1 = (hlen - get_freq(l, l+hlen-1, c)) + mincost(l + hlen, r, c+1);
    int cost2 = (hlen - get_freq(l+hlen, r-1, c)) + mincost(l, l + hlen, c+1);
    return min(cost1, cost2);
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    while (t--) {
        cin >> n >> s;
        rep(i,0,26) {
            int f = 0;
            rep(j,0,n) {
                if (s[j]-'a' == i) f++;
                freq[i][j] = f;
            }
        }
        cout << mincost(0, n, 'a') << '\n';
    }    
    return 0;
}