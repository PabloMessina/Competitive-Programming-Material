// tags: implementation
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define umap unordered_map
// -------------------------------
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    string s; cin >> s;
    umap<char,int> count;
    for (char c : s) count[c]++;
    int d1 = abs(count['L']  - count['R']);
    int d2 = abs(count['U']  - count['D']);
    if ( ((d1&1) + (d2&1)) & 1 ) {
        cout << "-1\n";
    } else {
        cout << ( (d1/2) + (d2/2) + ((d1&1) + (d2&1))/2 ) << '\n';
    }
    return 0;
}