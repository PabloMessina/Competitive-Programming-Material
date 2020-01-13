// tags: implementation, adhoc
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
        vector<int> f(26, 0);
        vector<int> idxs;
        rep(i,0,n) {
            if (s[i] != t[i]) {
                idxs.push_back(i);
                f[s[i]-'a']++;
                f[t[i]-'a']++;
            }
        }
        bool possible = true;
        for (int x : f) {
            if (x & 1) {
                possible = false;
                break;
            }
        }
        if (possible) {
            cout << "Yes\n";
            if (idxs.size() > 0) {
                int m = idxs.size();
                vector<pair<int,int>> swaps;
                rep(i,0,m) {
                    char a = s[idxs[i]];
                    char b = t[idxs[i]];
                    if (a != b) {
                        rep(j,i+1, m) {
                            if (s[idxs[j]] == a) {
                                swap(s[idxs[j]], t[idxs[i]]);
                                swaps.emplace_back(idxs[j]+1, idxs[i]+1);
                                break;
                            }
                            if (t[idxs[j]] == a) {
                                swap(s[idxs[j]], t[idxs[j]]);
                                swaps.emplace_back(idxs[j]+1, idxs[j]+1);
                                swap(s[idxs[j]], t[idxs[i]]);
                                swaps.emplace_back(idxs[j]+1, idxs[i]+1);
                                break;                                
                            }
                        }
                    }
                }
                cout << swaps.size() << '\n';
                for (auto& s : swaps) {
                    cout << s.first << ' ' << s.second << '\n';
                }
            }
        } else {
            cout << "No\n";
        }
    }
    return 0;
}