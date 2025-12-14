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
    int q;
    cin >> q;
    multiset<int> starts;
    multiset<int> ends;
    while (q--) {
        string op;
        int l, r;
        cin >> op >> l >> r;
        if (op == "+") {
            starts.insert(l);
            ends.insert(r);
        } else {
            auto it = starts.find(l);
            if (it != starts.end()) {
                starts.erase(it);
            }
            it = ends.find(r);
            if (it != ends.end()) {
                ends.erase(it);
            }
        }
        if (starts.size() < 2) {
            cout << "NO\n";
            continue;
        }
        int max_start = *starts.rbegin();
        int min_end = *ends.begin();
        if (max_start <= min_end) {
            cout << "NO\n";
        } else {
            cout << "YES\n";
        }
    }
    return 0;
}