// TODO: fix bugs
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
int increase(int i, int n) {
    return (i + 1) % n;
}
int decrease(int i, int n) {
    return (i - 1 + n) % n;
}
int shift(int i, int n, int k) {
    return (i + k + n) % n;
}
int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    int t; cin >> t;
    while (t--) {
        int n, x, y; cin >> n >> x >> y;
        vector<int> pos(x);
        rep(i,0,x) cin >> pos[i];
        sort(pos.begin(), pos.end());
        int count = 0;
        int i = 0, j = 0;
        while (true) {
            if (increase(j, x) == i) {
                if (shift(pos[j], n, 2) == pos[i]) {
                    count++;
                }
                break;
            }
            // Option 1: move j to the right (clockwise)
            int jj = increase(j, x);
            if (i == j) {
                if (shift(pos[i], n, 2) == pos[jj]) {
                    count++;
                    j = jj;
                    continue;
                }
            } else {
                if (shift(pos[j], n, 2) == pos[jj]) {
                    count += 2;
                    j = jj;
                    continue;
                }
            }
            // Option 2: move i to the left (counter-clockwise)
            int ii = decrease(i, x);
            if (i == j) {
                if (shift(pos[ii], n, 2) == pos[j]) {
                    count++;
                    i = ii;
                    continue;
                }
            } else {
                if (shift(pos[ii], n, 2) == pos[i]) {
                    count += 2;
                    i = ii;
                    continue;
                }
            }
            // if we reach this point, we move j by default
            if (i != j) count++;
            j = jj;
        }
        cout << count << '\n';
    }
    return 0;
}