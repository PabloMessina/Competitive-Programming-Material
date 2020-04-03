#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
// defines
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
#define umap unordered_map
#define uset unordered_set
// typedefs
typedef unsigned long long int ull;
typedef long long int ll;
// -------------------------------
string s1, s2, evil;
int n;
string predecessor(string& s) {
    int k = s.size();
    string s2(k, 0);
    invrep(i, k-1, 0) {
        if (s[i] > 'a') {
            s2[i] = s[i] - 1;
            rep(j,0,i) s2[j] = s[j];
            rep(j,)
        }
    }
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    while (cin >> n >> s1 >> s2 >> evil) {

    }
    return 0;
}