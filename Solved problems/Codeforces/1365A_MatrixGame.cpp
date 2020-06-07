// tags: greedy, implementation
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
int a[50][50];
int n, m;
bool is_free(int r, int c) {
    rep(i,0,m) if (a[r][i] == 1) return false;
    rep(i,0,n) if (a[i][c] == 1) return false;
    return true;
}
int main() {
    ios::sync_with_stdio(false); 
    cin.tie(0);
    int t; cin >> t;
    nextcase:
    while (t--) {
        cin >> n >> m;
        rep(i,0,n) rep(j,0,m) cin >> a[i][j];
        int turn = 0;
        while (true) {
            rep(r,0,n) rep(c,0,m) {
                if (is_free(r,c)) {
                    a[r][c] = 1;
                    goto nextturn;
                }
            }
            cout << (turn ? "Ashish\n" : "Vivek\n");
            goto nextcase;
            nextturn:;
            turn = 1 - turn;
        }
    }
    return 0;
}