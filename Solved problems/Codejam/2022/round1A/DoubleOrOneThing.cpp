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
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    rep(k,1,t+1) {
        string s; cin >> s;
        string o = "";
        int n = s.size();
        int i = 0;
        while (i < n) {
            int j = i;
            while (j+1 < n and s[j+1] == s[i]) ++j;
            if (j+1 < n and s[i] < s[j+1]) {
                rep(k,i,j+1) { o += s[i]; o += s[i]; }
            } else {
                rep(k,i,j+1) { o += s[i]; }
            }
            i = j + 1;
        }        
        cout << "Case #" << k << ": " << o << '\n';
    }
    return 0;
}