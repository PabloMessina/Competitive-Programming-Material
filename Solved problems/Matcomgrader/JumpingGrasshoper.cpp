// tags: implementation, std::set
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;
#define rep(i,a,b) for(int i = a; i < b; ++i)
#define invrep(i,b,a) for(int i = b; i >= a; --i)
// -------------------------------
int N, M, H[200000];
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0); cout.tie(0);
    cin >> N >> M;
    rep(i,0,N) cin >> H[i];
    set<int> set_f;
    set<int, greater<int>> set_b;
    int tmp = -1;
    rep(i,0,N) {
        tmp = max(tmp, H[i]);
        if (H[i] == tmp) set_f.insert(i);
    }
    tmp = -1;
    invrep(i,N-1,0) {
        tmp = max(tmp, H[i]);
        if (H[i] == tmp) set_b.insert(i);
    }
    while (M--) {
        char c; cin >> c;
        if (c == 'U') {
            int i, h; cin >> i >> h; --i;            
            { // forward
                auto it = set_f.lower_bound(i);
                auto stop_it = it;
                auto end_it = set_f.end();
                while (stop_it != end_it and H[*stop_it] < h) ++stop_it;
                if (stop_it != it) {
                    set_f.erase(it, stop_it);
                    set_f.insert(i);
                } else if (H[*prev(it)] < h) {
                    set_f.insert(i);
                }
            }
            { // backward
                auto it = set_b.lower_bound(i);
                auto stop_it = it;
                auto end_it = set_b.end();
                while (stop_it != end_it and H[*stop_it] < h) ++stop_it;
                if (stop_it != it) {
                    set_b.erase(it, stop_it);
                    set_b.insert(i);
                } else if (H[*prev(it)] < h) {
                    set_b.insert(i);
                }
            }
            H[i] = h;
        } else {
            int i; cin >> i; --i;            
            { // forward
                auto it = set_f.lower_bound(i);
                if (it != set_f.end()) {
                    if (*it == i) {
                        if (c == 'L') {
                            cout << i+1 << '\n';
                        } else if (next(it) != set_f.end()) {
                            cout << *next(it) + 1 << '\n';
                        } else {
                            cout << i+1 << '\n';
                        }
                    } else {
                        cout << *it + 1 << '\n';
                    }
                    continue;
                }                
            }            
            { // backward
                auto it = set_b.lower_bound(i);
                if (*it == i) {
                    if (c == 'R') {
                        cout << i+1 << '\n';
                    } else if (next(it) != set_b.end()) {
                        cout << *next(it) + 1 << '\n';
                    } else {
                        cout << i+1 << '\n';
                    }
                } else {
                    cout << *it + 1 << '\n'; 
                }
            }
        }
    }
    return 0;
}