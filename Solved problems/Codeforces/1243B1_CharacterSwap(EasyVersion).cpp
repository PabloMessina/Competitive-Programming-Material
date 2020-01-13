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
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    int k; cin >> k;
    while (k--) {
        int n; cin >> n;
        string s, t;
        cin >> s >> t;
        vector<int> idxs;
        rep(i,0,n) {
            if (s[i] != t[i]) {
                idxs.push_back(i);
                if (idxs.size() > 2) {
                    cout << "No\n";
                    goto end;
                }
            }
        }
        if (idxs.size() == 0) {
            cout << "Yes\n";
            continue;
        }
        if (idxs.size() == 2) {
            int i = idxs[0];
            int j = idxs[1];
            if (s[i] == s[j] and t[i] == t[j]) {
                cout << "Yes\n";
                continue;
            }
        }
        cout << "No\n";
        end:;
    }
    return 0;
}